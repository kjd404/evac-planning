# Comments 
# Here
set terminal png
set output 'new_composite_tts_graph.png'

set xrange [0:1]
set yrange [0:1]

set xlabel "Simulation time, t (hours)"
set ylabel "Fitness"

set key bottom right
set key font ",8"

# Line Types
#  First set
set style line 1 lt 1 lc 1 lw 2
set style line 2 lt 1 lc 2 lw 2
set style line 3 lt 1 lc 3 lw 2
set style line 4 lt 1 lc 4 lw 2
set style line 5 lt 1 lc 5 lw 2
set style line 6 lt 1 lc 6 lw 2
set style line 7 lt 1 lc 7 lw 2
set style line 8 lt 1 lc 8 lw 2
set style line 9 lt 1 lc 9 lw 2
set style line 10 lt 1 lc 10 lw 2
set style line 11 lt 1 lc 11 lw 2
set style line 12 lt 1 lc 12 lw 2

#  error lines set
set style line 13 lt 1 lc rgb "black" lw 1
set style line 14 lt 1 lc rgb "black" lw 1
set style line 15 lt 1 lc rgb "black" lw 1

# Plot for capacity data
plot "capacity_tts_1.dat" using 1:2 with lines ls 1 title "Cap TTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "capacity_tts_2.dat" using 1:2 with lines ls 2 title "Cap TTS-2", "" using 1:2:3 with errorbars ls 14 notitle,\
     "capacity_tts_3.dat" using 1:2 with lines ls 3 title "Cap TTS-3", "" using 1:2:3 with errorbars ls 15 notitle,\
     "agents_tts_1.dat" using 1:2 with lines ls 4 title "Agt TTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "agents_tts_2.dat" using 1:2 with lines ls 5 title "Agt TTS-2", "" using 1:2:3 with errorbars ls 14 notitle,\
     "agents_tts_3.dat" using 1:2 with lines ls 6 title "Agt TTS-3", "" using 1:2:3 with errorbars ls 15 notitle,\
     "topology_tts_1.dat" using 1:2 with lines ls 7 title "Top TTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "topology_tts_2.dat" using 1:2 with lines ls 8 title "Top TTS-2", "" using 1:2:3 with errorbars ls 14 notitle,\
     "topology_tts_3.dat" using 1:2 with lines ls 9 title "Top TTS-3", "" using 1:2:3 with errorbars ls 15 notitle,\
     "safety_tts_1.dat" using 1:2 with lines ls 10 title "Safety TTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "safety_tts_2.dat" using 1:2 with lines ls 11 title "Safety TTS-2", "" using 1:2:3 with errorbars ls 14 notitle,\
     "safety_tts_3.dat" using 1:2 with lines ls 12 title "Safety TTS-3", "" using 1:2:3 with errorbars ls 15 notitle

