#include <stdio.h>
#include <stdlib.h>

//These functions are to be used in test_linear.c to execute the enccassary tests

//timeing??

//maybe its better to start calling these thigns through Cython in a 
//Jupyter notebook that way we can easily ocmapre graph times?
//Pobablly too much work though when we can jsut output to terminal quickly.. :(
void efficency(){

	//do stuff...

}

//print matrix 
void print_matrix(Matrix matrix){
	printf("%f %f %f\n", matrix.a.x, matrix.b.x, matrix.c.x);
	printf("%f %f %f\n", matrix.a.y, matrix.b.y, matrix.c.y);
	printf("%f %f %f\n", matrix.a.z, matrix.b.z, matrix.c.z);
}

//prints vector 
void print_vector(fVector vector){
	printf("%f\n", vector.x);
	printf("%f\n", vector.y);
	printf("%f\n", vector.z);
}

void print_assess(double time1, double time2){
	double improvement = abs((time1 - time2)/time1);
	printf("The efficiency improvement is: %lf.\n", improvement);
}
//print NEON vector

//print NEON matrix




