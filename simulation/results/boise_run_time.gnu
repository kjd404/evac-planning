set terminal png
set output 'boise_runtime_graph.png'

set xrange [0:1000]
set yrange [0:60]
set title "Run times for Boise"
set xlabel "Number of randomly placed agent groups"
set ylabel "Run time"

set key bottom right

set style line 1 lt 1 lc rgb "black" lw 2

plot "boise_run_time_data.dat" using 1:2 with lines ls 1 title "Run Time"
