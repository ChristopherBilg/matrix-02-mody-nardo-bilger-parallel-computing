#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
void compare_matrices(double* a, double* b, int nRows, int nCols);
int getNumberOfLines(char *filename);
int **extractMatrixFromFile(char *filename);
int getArrayLength(double *arr);

//Per the word doc requirements to automate matrix input,
//this function is used to calculate the number of columns
//of the inputted matrix, and, as such, both col and row
//number because only square matrices are used.
int getNumberOfLines(char *filename)
{
    int count = 0; // Line counter (result)
    char c; // To store a character read from file
    
    // Get file name from user. The file should be
    // either in current folder or complete path should be provided
    
    // Open the file
    FILE *fp = fopen(filename, "r");
    
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
    
    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n' || c == EOF) // Increment count if this character is newline
            count = count + 1;
    
    // Close the file
    rewind(fp);
    fclose(fp);
    
    return count;
}

//gets the matrix from the file sent via command line in the main
//filename is the pointer to the string file name, nrows is the number of rows

//doesnt yet work with my testing, causes a seg fault 11
double* extractMatrixFromFile(char *filename, int nrows)
{
    printf("extractMatrixFromFile");
    FILE *fp = fopen(filename, "r");
    char str[256];
    int i = 0;
    char *tok = strtok(str, " ");
    double *extractedMatrix = malloc(sizeof(double) * nrows * nrows);
    printf("after malloc");
    
    
    if (fp != NULL)
    {
        while (fgets(str, 256, fp) != NULL)
        {
            printf("%s", str);
            while(strcmp(tok, "\n") != 0)
            {
                double tempVal = atof(tok);
                extractedMatrix[i++] = tempVal;
                tok = strtok (NULL, " ");
            }
        }
    }
    else
    {
        printf("Could not open file %s", filename);
    }
    
    rewind(fp);
    fclose(fp);

    return extractedMatrix;
}

int getArrayLength(double *arr)
{
    return (sizeof(arr)/sizeof(arr[0]));
}

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
  FILE *aamatrix = fopen(argv[0],"r");
  FILE *bbmatrix = fopen(argv[1],"r");

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  if (argc > 1) {
    nrows = getNumberOfLines(argv[0]);
    ncols = nrows;

return nrows;
    if (myid == 0) {
      // Master Code goes here
      // aa = gen_matrix(nrows, ncols);
      // bb = gen_matrix(ncols, nrows);
	      
      //Extract the matrix values from the respective text files.

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
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  fclose(aamatrix);
  fclose(bbmatrix);
  return 0;
}

