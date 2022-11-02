set terminal pdf
set output 'throughput.pdf'
set xlabel 'Zookeeper Servers'
set ylabel 'Throughput ops/sec'
set title 'Zookeeper Throughput'
set yrange[0:13000]
set xrange[0:7]
#use the first and second columns from the file throughput.dat
plot 'throughput.dat' using ($1):($2) title "throughput" with linespoints
