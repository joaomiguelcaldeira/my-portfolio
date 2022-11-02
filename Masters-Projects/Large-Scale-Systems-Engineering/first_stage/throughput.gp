set terminal pdf
set output 'throughput.pdf'
set xlabel 'Clients and Servers'
set ylabel 'Throughput ops/sec'
set title 'Zookeeper Throughput'
set yrange[2200:5500]
#use the first and second columns from the file throughput.dat
plot 'throughput.dat' using ($1):($2) title "throughput" with linespoints
