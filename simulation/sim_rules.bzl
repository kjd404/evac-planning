def _run_sim_drawable_impl(ctx):
    out = ctx.outputs.out
    scen = ctx.file.scenario
    sim = ctx.executable.sim
    city = ctx.attr.city

    cmd = """
set -euo pipefail
OUTDIR=$(dirname {out})
TMP="$OUTDIR/run_{name}"
rm -rf "$TMP"
mkdir -p "$TMP/outputs"
cp {scen} "$TMP/scen.slang"
EVAC_OUTPUT_DIR="$TMP/outputs" "{sim}" "$TMP/scen.slang"
cp "$TMP/outputs/{city}Final.txt" {out}
""".format(
        scen = scen.path,
        sim = sim.path,
        city = city,
        out = out.path,
        name = ctx.label.name,
    )

    ctx.actions.run_shell(
        inputs = [scen, sim],
        outputs = [out],
        command = cmd,
        progress_message = "Running simulator to produce drawable for %s" % city,
        use_default_shell_env = True,
    )

run_sim_drawable = rule(
    implementation = _run_sim_drawable_impl,
    attrs = {
        "scenario": attr.label(allow_single_file = True, mandatory = True),
        "city": attr.string(mandatory = True),
        "sim": attr.label(executable = True, cfg = "exec", default = Label("//simulation:evac")),
        "out": attr.output(mandatory = True),
    },
)

def _make_gif_impl(ctx):
    drawable = ctx.file.drawable
    out = ctx.outputs.out
    viz_py = ctx.file.viz_py
    width = ctx.attr.width
    fps = ctx.attr.fps
    duration = ctx.attr.duration
    edgewidth = ctx.attr.edgewidth
    trails_flag = "--trails" if ctx.attr.trails else ""

    cmd = """
set -euo pipefail
python3 "{viz_py}" --input {inp} --outfile {out} --width {w} --fps {fps} --duration {dur} --edgewidth {ew} {trails}
""".format(
        viz_py = viz_py.path,
        inp = drawable.path,
        out = out.path,
        w = width,
        fps = fps,
        dur = duration,
        ew = edgewidth,
        trails = trails_flag,
    )

    ctx.actions.run_shell(
        inputs = [drawable, viz_py],
        outputs = [out],
        command = cmd,
        progress_message = "Rendering GIF %s" % out.path,
        use_default_shell_env = True,
    )

make_gif = rule(
    implementation = _make_gif_impl,
    attrs = {
        "drawable": attr.label(allow_single_file = True, mandatory = True),
        "viz_py": attr.label(allow_single_file = True, default = Label("//simulation:tools/viz_gif.py")),
        "width": attr.int(default = 700),
        "fps": attr.int(default = 30),
        "duration": attr.string(default = "10"),
        "edgewidth": attr.string(default = "prob"),
        "trails": attr.bool(default = True),
        "out": attr.output(mandatory = True),
    },
)
