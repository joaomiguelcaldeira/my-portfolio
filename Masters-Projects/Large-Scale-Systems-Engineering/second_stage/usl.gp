set terminal pdf
set output 'usl.pdf'
l = 3183.0449249965
d = 0.2053051581
k = -0.0159011355
f(x) = ((l*x)/(1+d*(x - 1) + k*x*(x - 1)))
set xlabel 'Replicas'
set ylabel 'Throughput ops/sec'
set title 'USL and Throughput'
set yrange[2200:20000]
set xrange[0:7]
plot 'throughput.dat' using 1:(f($1)) title "usl" with linespoints, 'throughput.dat' using 1:2 title "throughput" with linespoints, 'perfect_linear.dat' using 1:2 title "ideal" with linespoints
