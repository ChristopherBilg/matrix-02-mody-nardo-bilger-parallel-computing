#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	double *m1 = extractMatrixFromFile("matrix1", 3);
	double *m2 = extractMatrixFromFile("matrix2", 3);
	double *m3 = gen_matrix(3, 3);
	mmult(m3, m1, 3, 3, m2, 3, 3);
	printToFile(m3, 3);
	return 1;
}
