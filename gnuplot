set datafile separator ","
set xlabel "Matrix Size (N x N)"
set ylabel "Time to Compute (seconds)"
set terminal png size 800,600 


set output "basic.png"
plot "basic.csv" title "Basic N x N Matrix Multiplication" with linespoints

set output "simd.png"
plot "simd.csv" title "SIMD Optimized N x N Matrix Multiplication" with linespoints

set output "openmp.png"
plot "openmp.csv" title "OpenMP Optimized N x N Matrix Multiplication" with linespoints

set output "combined.png"
set title "Matrix Multiplication on Wolfgang Cluster"
plot "basic.csv" title 'Basic' with linespoints, "simd.csv" title 'SIMD' with linespoints, "openmp.csv" title 'OpenMP' with linespoints
