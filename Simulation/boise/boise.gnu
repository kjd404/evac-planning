# Creates a point plot of the nodes in the boise graph
# Used to identify and create meaningful safety functions
set terminal png
set output 'boise_nodes.png'

set xrange[1398740:1462170]
set yrange[899870:950980]

set xlabel
set ylabel

# unset tics
unset key
# unset border

set title "Boise Nodes"

plot "nodes_coords.txt" using 2:3:1 w labels point offset character 1 tc rgb "blue"