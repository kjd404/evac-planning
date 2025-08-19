# Comments 
# Here
set terminal png
set output 'pop10s2dfxg.png'

set xrange [0:1000]
set yrange [0:1]

set xlabel "Number of Generations"
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
plot "pop10s2dGnuPlotInput.dat" using 1:2 with lines ls 1 notitle, "" using 1:2:3 with errorbars ls 13 notitle
