set terminal png
set output 'composite_gts.png'

set xrange [0:100]
set yrange [0:1]

set xlabel "Average generations, G"
set ylabel "Fitness"

set key bottom right
set key font ',15'

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

set style line 13 lt 1 lc rgb "black" lw 1


plot "agents_gts_1.dat" using 1:2 with lines ls 1 title "Agents GTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "agents_gts_2.dat" using 1:2 with lines ls 2 title "Agents GTS-2", "" using 1:2:3 with errorbars ls 13 notitle,\
     "agents_gts_3.dat" using 1:2 with lines ls 3 title "Agents GTS-3", "" using 1:2:3 with errorbars ls 13 notitle,\
     "capacity_gts_1.dat" using 1:2 with lines ls 4 title "Capacity GTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "capacity_gts_2.dat" using 1:2 with lines ls 5 title "Capacity GTS-2", "" using 1:2:3 with errorbars ls 13 notitle,\
     "capacity_gts_3.dat" using 1:2 with lines ls 6 title "Capacity GTS-3", "" using 1:2:3 with errorbars ls 13 notitle,\
     "safety_gts_1.dat" using 1:2 with lines ls 7 title "Safety GTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "safety_gts_2.dat" using 1:2 with lines ls 8 title "Safety GTS-2", "" using 1:2:3 with errorbars ls 13 notitle,\
     "safety_gts_3.dat" using 1:2 with lines ls 9 title "Safety GTS-3", "" using 1:2:3 with errorbars ls 13 notitle,\
     "topology_gts_1.dat" using 1:2 with lines ls 10 title "Topology GTS-1", "" using 1:2:3 with errorbars ls 13 notitle,\
     "topology_gts_2.dat" using 1:2 with lines ls 11 title "Topology GTS-2", "" using 1:2:3 with errorbars ls 13 notitle,\
     "topology_gts_3.dat" using 1:2 with lines ls 12 title "Topology GTS-3", "" using 1:2:3 with errorbars ls 13 notitle