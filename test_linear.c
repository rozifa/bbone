#include <stdio.h>
#include <time.h>
#include <arm_neon.h>
#include "linear_ops.h"
#include "neon_wrappers.h"
#include "test_functions.h"

//test function
// Here we want to call our various data structures 
// and associated operations to test their speed.
int main(){
	//Initalize test vectors
	/*
	fVector v1 = {.x = 37.0, .y = 25.69, .z = 73.0}; //arbitrary 
	fVector v2 = {.x = 2.0, .y = 15.15, .z = 36.63};
	fVector v3 = {.x = 93.93, .y = 16.0, .z = 7.0};

	fVector v4 = {.x = 130.234, .y = 2.4, .z = 8.25};
	fVector v5 = {.x = 234.0, .y = 1.7, .z = 9.25};
	fVector v6 = {.x = 224.0, .y = 5.234, .z = 12.25};

	//Initilize test matrices++
	Matrix m1 = {.a = v1, .b = v2, .c = v3};
	Matrix m2 = {.a = v4, .b = v5, .c = v6};

	//Neonize the vects
	float32x4_t neon_vector1 = fVector_wrapper(v1);
	float32x4_t neon_vector2 = fVector_wrapper(v2);
	float32x4_t neon_vector3 = fVector_wrapper(v3);

	float32x4_t neon_vector4 = fVector_wrapper(v4);
	float32x4_t neon_vector5 = fVector_wrapper(v5);
	float32x4_t neon_vector6 = fVector_wrapper(v6);


	//Test linear ops functions
	float det_m1; 
	det_m1 = determinant(m1);
	Cofactor com1;
	com1 = cofactor(m1);
	printf("The determinent of m1 is: %f.\n", det_m1);

	printf("%f %f\n", com1.one.a.x, com1.one.b.x);
	printf("%f %f\n", com1.one.a.y, com1.one.b.y);

	Matrix m3 = MatAdd(m1, m2);
	print_matrix(m3);

	Matrix m4 = MatSub(m3, m1);
	print_matrix(m4);

	fVector mv5 = transform(v1, m4);
	print_vector(mv5);

	Matrix tm2 = transpose(m2);
	print_matrix(tm2);

	Matrix tm2bym2 = mat_mult(m2, tm2);
	print_matrix(tm2bym2);

	Matrix tm2bym2_2 = MatrixByMatrixTranspose(m2, m2);
	print_matrix(tm2bym2_2);


    fVector vector2 = {};
    vector2=float32_to_fvector(neon_vector1); */
/*
    clock_t t;
    t = clock();

    //neon version
    float* v2fl = (float*)(&vector2);
    int i;
	//Test if conversion worked by printing entries 
    for (i = 0; i <= 3; i++){
		printf("READ FROM NEON VECTOR:\n");
		printf("The %d entry is: %f\n", i, neon_vector1[i]);
	}

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("NEON took %f seconds.\n", time_taken);

	clock_t t2 = clock();

	//struct version
	print_vector(vector2);
	
	t2 = clock() - t2;
	double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
	printf("STRUCT took %f seconds.\n", time_taken2); 
*/
/*
	clock_t t;
	t = clock();

	fVector test_vector1 = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_vector2 = {.x = 0.00101, .y = 0.000001, .z = 0.00001};
	int i = 0;
	int trials = 1000001;

	while (i <= trials){

		test_vector1 = VecAdd(test_vector1, test_vector2);
		i++;

	}

	t = clock() - t;
	double time_taken = (((double)t)/CLOCKS_PER_SEC);
	print_vector(test_vector1);
	printf("STRUCT took %f seconds.\n", time_taken); */
// ------------------------------------------------------ 
	fVector test_boy = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy2 = {.x = 0.00101, .y = 0.000001, .z = 0.00001};
	//convert the above
	float32x4_t neon_boy = fVector_wrapper(test_boy);
	float32x4_t neon_boy2 = fVector_wrapper(test_boy2);
	
	int j = 0;
	
	clock_t t2;
	t2 = clock();

	while (j <= trials){

		neon_boy = vaddq_f32(neon_boy, neon_boy2);
		j++;

	}

	t2 = clock() - t2;
	double time_taken2 = (((double)t)/CLOCKS_PER_SEC);
	fVector back_boy = float32_to_fvector(neon_boy);
	print_vector(back_boy);
	printf("NEON took %f seconds.\n", time_taken2); 

	


return 0;
}

//vmulq_f32() NEON Multiplication.