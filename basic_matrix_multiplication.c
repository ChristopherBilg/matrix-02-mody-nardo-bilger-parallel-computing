#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mmult.c"

int main(int argc, char** argv) {
	if(argc < 2) {
	  printf("Valid syntax: %s <int>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	if(!size || size < 1) {
	  printf("Valid syntax: %s <int>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Creating matrix 'a' of size %d x %d\n", size, size);
	double* a = gen_matrix(size, size);

	printf("Creating matrix 'b' of size %d x %d\n", size, size);
	double* b = gen_matrix(size, size);

	compare_matrices(a, b, size, size);

	printf("Multiplying matrix 'a' and 'b'\n");
	double* c = gen_matrix(size, size);
	int success = mmult(c, a, size, size, b, size, size);
}
