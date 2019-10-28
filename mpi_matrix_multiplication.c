#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);

/** 
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
*/

int main(int argc, char* argv[])
{
  int nrows, ncols;
  double *aa;	/* the A matrix */
  double *bb;	/* the B matrix */
  double *cc1;	/* A x B computed using the omp-mpi code you write */
  double *cc2;	/* A x B computed using the conventional algorithm */
  int myid, numprocs;
  double starttime, endtime;
  MPI_Status status;
  /* insert other global variables here */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  if (argc > 1) {
    nrows = atoi(argv[1]);
    ncols = nrows;
    if (myid == 0) {
      // Master Code goes here
	    
	
    MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
    for (i = 0; i < min(numprocs-1, nrows); i++) {
    	for (j = 0; j < ncols; j++) {
        	buffer[j] = aa[i * ncols + j];
    	}  
    	MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD);
    	numsent++;
     }
	for (i = 0; i < nrows; i++) {
    MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, 
        MPI_COMM_WORLD, &status);
    sender = status.MPI_SOURCE;
    anstype = status.MPI_TAG;
    c[anstype-1] = ans;
    if (numsent < nrows) {
        for (j = 0; j < ncols; j++) {
            buffer[j] = aa[numsent*ncols + j];
        }  
        MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1, 
                 MPI_COMM_WORLD);
        numsent++;
    } else {
        MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0,
                 MPI_COMM_WORLD);
    }
	}	    
	    
	    
      aa = gen_matrix(nrows, ncols);
      bb = gen_matrix(ncols, nrows);
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      endtime = MPI_Wtime();
      printf("%f\n",(endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      compare_matrices(cc2, cc1, nrows, nrows);
    } else {
      // Slave Code goes here
	    
	MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
	if (myid <= nrows) {
    	while(1) {
        	MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_TAG == 0){ break; }
        row = status.MPI_TAG;
        ans = 0.0;
        for (j = 0; j < ncols; j++) {
            ans += buffer[j] * b[j];
        }
        MPI_Send(&ans, 1, MPI_DOUBLE, master, row,
                 MPI_COMM_WORLD);
    	}
	}

	    
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}
