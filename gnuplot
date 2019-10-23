set datafile separator ","
set xlabel "Matrix Size (N x N)"
set ylabel "Time to Compute (seconds)"
set terminal pngcairo
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5
set pointintervalbox 3

set output "basic.png"
plot "basic.csv" title "Basic N x N Matrix Multiplication" with linespoints ls 1

set output "simd.png"
plot "simd.csv" title "SIMD Optimized N x N Matrix Multiplication" with linespoints ls 1

set output "openmp.png"
plot "openmp.csv" title "OpenMP Optimized N x N Matrix Multiplication" with linespoints ls 1

set output "combined.png"
plot "basic.csv" title 'Basic' with linespoints ls 1, "simd.csv" title 'SIMD' with linespoints ls 1, "openmp.csv" title 'OpenMP' with linespoints ls 1
