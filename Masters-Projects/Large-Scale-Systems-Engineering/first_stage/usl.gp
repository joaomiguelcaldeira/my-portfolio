set terminal pdf
set output 'usl.pdf'
l = 2845.2309970244
d = 0.2692010226
k = 0.0310961856
f(x) = ((l*x)/(1+d*(x - 1) + k*x*(x - 1)))
set xlabel 'Clients and Servers'
set ylabel 'Throughput ops/sec'
set title 'USL and Throughput'
set yrange[2200:5700]
set xrange[1:10]
plot 'throughput.dat' using 1:(f($1)) title "usl" with linespoints, 'throughput.dat' using 1:2 title "throughput" with linespoints
