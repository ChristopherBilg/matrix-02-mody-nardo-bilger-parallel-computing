PGMS=mmult_omp_timing matrix_times_vector hello pi mxv_omp_mpi mmult_mpi_omp basic_matrix_multiplication basic_simd_multiplication openmp_matrix_multiplication

all:	${PGMS}

mmult_mpi_omp:		mmult.o mmult_mpi_omp.o
	mpicc -o mmult_mpi_omp -fopenmp -O3 mmult.o mmult_mpi_omp.o

mmult_mpi_omp.o:	mmult_mpi_omp.c
	mpicc -c -fopenmp -O3 mmult_mpi_omp.c

mmult_omp_timing:	mmult.o mmult_omp.o mmult_omp_timing.o
	gcc -o mmult -fopenmp -O3 mmult.o mmult_omp.o mmult_omp_timing.o -o mmult_omp_timing

mmult.o:	mmult.c
	gcc -c -O3 mmult.c

mmult_omp.o:	mmult_omp.c
	gcc -c -O3 -fopenmp mmult_omp.c

mmult_omp_timing.o:	mmult_omp_timing.c
	gcc -c -O3 mmult_omp_timing.c

matrix_times_vector:	matrix_times_vector.c
	mpicc -O3 -o matrix_times_vector matrix_times_vector.c

basic_matrix_multiplication:	basic_matrix_multiplication.c
	mpicc -o basic_matrix_multiplication basic_matrix_multiplication.c
	mpicc -O3 -o basic_simd_multiplication basic_matrix_multiplication.c

openmp_matrix_multiplication: openmp_matrix_multiplication.c
	gcc -O3 -fopenmp openmp_matrix_multiplication.c -o openmp_matrix_multiplication

hello:	hello.c
	mpicc -O3 -o hello hello.c

pi:	pi.c
	mpicc -O3 -o pi pi.c

mxv_omp_mpi:	mxv_omp_mpi.c
	mpicc -fopenmp -O3 -o mxv_omp_mpi mxv_omp_mpi.c

clean:
	rm -rf automation_files/
	rm -f *.csv
	rm -f *.txt
	rm -f *.o
	rm -f ${PGMS}

