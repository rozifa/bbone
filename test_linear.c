#include <stdio.h>
#include <arm_neon.h>
#include "linear_ops.h"
#include "neon_wrappers.h" 

//test function
// Here we want to call our various data structures 
// and associated operations to test their speed.
int main(){
	//Initalize test vectors

	fVector v1 = {.x = 3.5f, .y = 3.14f, .z = 4.3f}; //arbitrary 
	fVector v2 = {.x = 7.69f, .y = 10.0f, .z = 96.2f};
	fVector v3 = {.x = 2.23f, .y = 1.234f, .z = 3.12f};

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

    fVector vector2 = {};
    vector2=float32_to_fvector(neon_vector1);

    float* v2fl = (float*)(&vector2);
    int i;
	//Test if conversion worked by printing entries 
    for (i = 0; i <= 3; i++){
		printf("The %d entry is: %f\n", i, neon_vector1[i]);
	}

	//Test linear ops functions
	float det_m1; 
	det_m1 = determinant(m1);
	float* dm1 = (float*)(&det_m1);
	printf("The determinent of m1 is: %d\n.", det_m1);

return 0;
}