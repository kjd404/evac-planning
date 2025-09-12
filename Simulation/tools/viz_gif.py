#!/usr/bin/env python3
import argparse
import math
import os
from collections import defaultdict, deque
from typing import Dict, List, Tuple

try:
    from PIL import Image, ImageDraw, ImageFont
except Exception as e:
    raise SystemExit("Pillow (PIL) is required: pip install Pillow")


def parse_drawable(path: str):
    edges: Dict[int, Tuple[int, int, float]] = {}
    nodes: Dict[int, Dict] = {}
    node_probs: Dict[int, List[Tuple[int, float]]] = defaultdict(list)
    routes: Dict[int, List[int]] = {}
    times: Dict[int, List[float]] = {}
    groups: Dict[int, int] = {}

    curr_node = None
    with open(path, "r") as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            parts = line.split()
            tag = parts[0]
            try:
                if tag == "e":
                    # e <edge_id> <from_id> <to_id> <safety>
                    eid, frm, to, saf = int(parts[1]), int(parts[2]), int(parts[3]), float(parts[4])
                    edges[eid] = (frm, to, saf)
                elif tag == "n":
                    # n <node_id> <capacity> <safety> <x> <y>
                    nid = int(parts[1])
                    nodes[nid] = {
                        "capacity": int(parts[2]),
                        "safety": float(parts[3]),
                        "x": float(parts[4]),
                        "y": float(parts[5]),
                    }
                    curr_node = nid
                elif tag == "p":
                    if curr_node is not None:
                        eid, prob = int(parts[1]), float(parts[2])
                        node_probs[curr_node].append((eid, prob))
                elif tag == "a":
                    aid = int(parts[1])
                    route = [int(x) for x in parts[2:]]
                    routes[aid] = route
                elif tag == "t":
                    aid = int(parts[1])
                    ts = [float(x) for x in parts[2:]]
                    times[aid] = ts
                elif tag == "g":
                    aid = int(parts[1])
                    groups[aid] = int(parts[2])
                else:
                    # ignore unknown tags
                    pass
            except Exception:
                # skip malformed line but continue
                continue

    return nodes, edges, node_probs, routes, times, groups


def compute_layout(nodes: Dict[int, Dict], width: int, margin: int = 40):
    xs = [n["x"] for n in nodes.values()]
    ys = [n["y"] for n in nodes.values()]
    if not xs or not ys:
        raise ValueError("No node coordinates in drawable file")
    minx, maxx = min(xs), max(xs)
    miny, maxy = min(ys), max(ys)
    spanx = max(1e-6, maxx - minx)
    spany = max(1e-6, maxy - miny)

    # preserve aspect ratio
    scale = (width - 2 * margin) / spanx
    height = int(spany * scale + 2 * margin)

    def to_px(nid: int):
        nx, ny = nodes[nid]["x"], nodes[nid]["y"]
        px = int((nx - minx) * scale) + margin
        # y grows downward on canvas; invert
        py = height - (int((ny - miny) * scale) + margin)
        return px, py

    return to_px, height


def aggregate_edge_weights_by_prob(edges, node_probs):
    # Sum probabilities across nodes for each edge id
    weights = defaultdict(float)
    for nid, plist in node_probs.items():
        for eid, p in plist:
            weights[eid] += p
    return weights


def build_edge_lookup(edges):
    # Map (from,to) -> (edge_id, safety)
    lu = {}
    for eid, (frm, to, saf) in edges.items():
        lu[(frm, to)] = (eid, saf)
    return lu


def lerp(a, b, t):
    return a + (b - a) * t


def main():
    ap = argparse.ArgumentParser(description="Animate evacuation routes to a GIF")
    ap.add_argument("--input", required=True, help="Drawable output file (outputs/<City>Final.txt)")
    ap.add_argument("--outfile", required=True, help="Output GIF path")
    ap.add_argument("--width", type=int, default=700, help="GIF width in pixels (default 700)")
    ap.add_argument("--fps", type=int, default=30, help="Frames per second (default 30)")
    ap.add_argument("--duration", type=float, default=10.0, help="Duration in seconds (default 10)")
    ap.add_argument("--edgewidth", choices=["prob", "const"], default="prob", help="Edge width mode")
    ap.add_argument("--trails", action="store_true", help="Enable agent trails")
    ap.add_argument("--trail_frames", type=int, default=15, help="Frames to keep in trails")
    ap.add_argument("--no_group_scale", action="store_true", help="Disable dot size scaling by group size")
    args = ap.parse_args()

    nodes, edges, node_probs, routes, times, groups = parse_drawable(args.input)
    to_px, height = compute_layout(nodes, args.width)

    # Canvas base
    bg = Image.new("RGBA", (args.width, height), (255, 255, 255, 255))
    base = bg.copy()
    draw = ImageDraw.Draw(base)

    # Edge widths
    ew = defaultdict(lambda: 1.5)
    if args.edgewidth == "prob":
        agg = aggregate_edge_weights_by_prob(edges, node_probs)
        # normalize
        vmax = max(agg.values()) if agg else 1.0
        for eid, val in agg.items():
            ew[eid] = 1.5 + 4.0 * (val / vmax)

    # Draw edges
    for eid, (frm, to, saf) in edges.items():
        x1, y1 = to_px(frm)
        x2, y2 = to_px(to)
        # color by safety (gray to blue for 0..1)
        c = int(180 + 75 * saf)
        col = (c, c, 255 if saf > 0 else 180, 255)
        draw.line((x1, y1, x2, y2), fill=col, width=int(ew[eid]))

    # Draw nodes
    for nid, n in nodes.items():
        x, y = to_px(nid)
        r = 5
        safety = n.get("safety", 0.0)
        col = (int(255 * (1.0 - safety)), int(50 + 205 * safety), 50, 255)
        draw.ellipse((x - r, y - r, x + r, y + r), fill=col, outline=(0, 0, 0, 255))

    # Precompute useful maps
    edge_lookup = build_edge_lookup(edges)
    max_time = 0.0
    for aid, rt in times.items():
        if rt:
            max_time = max(max_time, rt[-1])
    if max_time <= 0:
        # fallback to uniform timing if no times
        for aid, route in routes.items():
            times[aid] = [i for i in range(len(route))]
            max_time = max(max_time, times[aid][-1] if times[aid] else 0)

    # Animation parameters
    total_frames = max(1, int(args.fps * args.duration))
    frames: List[Image.Image] = []

    # Trails storage
    trails: Dict[int, deque] = {}
    if args.trails:
        trails = {aid: deque([], maxlen=max(1, args.trail_frames)) for aid in routes}

    # Render frames
    for fi in range(total_frames):
        t_now = (fi / (total_frames - 1)) * max_time if total_frames > 1 else 0.0
        frame = base.copy()
        fd = ImageDraw.Draw(frame)

        # Agents
        for aid, route in routes.items():
            rt = times.get(aid, [])
            if not route:
                continue
            # Clamp if times missing
            if not rt or len(rt) != len(route):
                rt = [i for i in range(len(route))]
            # Find segment
            idx = 0
            while idx + 1 < len(rt) and t_now >= rt[idx + 1]:
                idx += 1
            if idx >= len(route) - 1:
                # agent at last node
                x, y = to_px(route[-1])
                curr_col = (30, 144, 255, 255)  # default blue
            else:
                n0, n1 = route[idx], route[idx + 1]
                t0, t1 = rt[idx], rt[idx + 1]
                frac = 0.0 if t1 == t0 else (t_now - t0) / (t1 - t0)
                frac = max(0.0, min(1.0, frac))
                x0, y0 = to_px(n0)
                x1, y1 = to_px(n1)
                x = int(lerp(x0, x1, frac))
                y = int(lerp(y0, y1, frac))
                # color by edge safety if known
                saf = 0.0
                if (n0, n1) in edge_lookup:
                    saf = edge_lookup[(n0, n1)][1]
                curr_col = (30, 144, 255, 255) if saf >= 1.0 else (200, 50, 50, 220)

            # Trails
            if args.trails:
                tr = trails[aid]
                tr.append((x, y))
                # Draw trailing dots
                alpha_step = int(140 / max(1, len(tr)))
                a_val = 40
                for (tx, ty) in list(tr)[:-1]:
                    fd.ellipse((tx - 2, ty - 2, tx + 2, ty + 2), fill=(100, 100, 100, a_val))
                    a_val = min(180, a_val + alpha_step)

            # Dot size by group size
            members = groups.get(aid, 1)
            if args.no_group_scale:
                r = 3
            else:
                r = max(2, int(2 + math.sqrt(max(1, members)) * 0.8))
            fd.ellipse((x - r, y - r, x + r, y + r), fill=curr_col, outline=None)

        # Add to frames (convert to palette to shrink GIF size)
        # Progress bar in bottom margin
        try:
            progress = 0.0 if total_frames <= 1 else fi / (total_frames - 1)
            bar_x0, bar_x1 = 40, args.width - 40
            bar_y0, bar_y1 = height - 28, height - 12
            # baseline
            fd.rectangle((bar_x0, bar_y0, bar_x1, bar_y1), fill=(240, 240, 240, 255), outline=(180, 180, 180, 255))
            prog_x = int(bar_x0 + progress * (bar_x1 - bar_x0))
            fd.rectangle((bar_x0, bar_y0, prog_x, bar_y1), fill=(50, 150, 255, 210))
            # percentage text
            pct = int(progress * 100)
            fd.text((bar_x1 - 44, bar_y0 - 12), f"{pct}%", fill=(0, 0, 0, 255))
        except Exception:
            pass

        frames.append(frame.convert("P", palette=Image.ADAPTIVE))

    # Save GIF
    os.makedirs(os.path.dirname(args.outfile) or ".", exist_ok=True)
    frames[0].save(
        args.outfile,
        save_all=True,
        append_images=frames[1:],
        duration=int(1000 / args.fps),
        loop=0,
        optimize=False,
        disposal=2,
    )


if __name__ == "__main__":
    main()
