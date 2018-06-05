#include <stdio.h>

//These functions are to be used in test_linear.c to execute the enccassary tests

//print entries of a neon array 
void print_matrix(Matrix matrix){
	printf("%f %f %f\n", matrix.a.x, matrix.b.x, matrix.c.x);
	printf("%f %f %f\n", matrix.a.y, matrix.b.y, matrix.c.y);
	printf("%f %f %f\n", matrix.a.z, matrix.b.z, matrix.c.z);
}

void print_vector(fVector vector){
	printf("%f\n", vector.x);
	printf("%f\n", vector.y);
	printf("%f\n", vector.z);
}


