# Comments 
# Here
set terminal png
set output 'bazzan_tts_graph.png'

set xrange [0:2.2]
set yrange [0:1]
set title "Time to safety for Bazzan comparison test"
set xlabel "Simulation time in hours (t)" font ",10"
set ylabel "Fitness(t)" font ",10"

set key bottom right
set key font ",15"

# Line Types
#  First set
set style line 1 lt 1 lc rgb "black" lw 2
set style line 2 lt 1 lc rgb "red" lw 2
set style line 3 lt 1 lc rgb "blue" lw 2

#  Second set
set style line 4 lt 2 lc rgb "black" lw 2
set style line 5 lt 2 lc rgb "red" lw 2
set style line 6 lt 2 lc rgb "blue" lw 2

#  Third set
set style line 7 lt 3 lc rgb "black" lw 2
set style line 8 lt 3 lc rgb "red" lw 2
set style line 9 lt 3 lc rgb "blue" lw 2

#  Fourth set
set style line 10 lt 4 lc rgb "black" lw 2
set style line 11 lt 4 lc rgb "red" lw 2
set style line 12 lt 4 lc rgb "blue" lw 2

#  error lines set
set style line 13 lt 1 lc rgb "black" lw 1
set style line 14 lt 1 lc rgb "red" lw 1
set style line 15 lt 1 lc rgb "blue" lw 1

# Plot for capacity data
plot "bazzan_tts.dat" using 1:2 with lines ls 1 title "Comparison Test TTS-1", "" using 1:2:3 with errorbars ls 13 title "Comparison Test TTS-1 std dev"
