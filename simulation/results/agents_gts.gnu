set terminal png
set output 'agents_gts.png'

set xrange [0:100]
set yrange [0:1]

set xlabel "Average generations, G"
set ylabel "Fitness"

set key bottom right
set key font ',15'

set style line 1 lt 1 lc rgb "black" lw 2
set style line 2 lt 2 lc rgb "blue" lw 2
set style line 3 lt 3 lc rgb "red" lw 2

set style line 4 lt 1 lc rgb "black" lw 1
set style line 5 lt 2 lc rgb "blue" lw 1
set style line 6 lt 3 lc rgb "red" lw 1

plot "agents_gts_1.dat" using 1:2 with lines ls 1 title "Agents GTS-1", "" using 1:2:3 with errorbars ls 4 notitle,\
     "agents_gts_2.dat" using 1:2 with lines ls 2 title "Agents GTS-2", "" using 1:2:3 with errorbars ls 5 notitle,\
     "agents_gts_3.dat" using 1:2 with lines ls 3 title "Agents GTS-3", "" using 1:2:3 with errorbars ls 6 notitle
