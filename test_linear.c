#include <stdio.h>
#include <arm_neon.h>
#include "linear_ops.h"
#include "neon_wrappers.h" 

//test function
// Here we want to call our various data structures 
// and associated operations to test their speed.
int main(){
	//Initalize test vectors

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
	Cofactor com1;
	com1 = cofactor(m1);
	printf("The determinent of m1 is: %f.\n", det_m1);

	printf("%f %f\n", com1.one.a.x, com1.one.b.x);
	printf("%f %f\n", com1.one.a.y, com1.one.b.y);

	Matrix m3 = MatAdd(m1, m2);
	printf("%f %f %f", m3.a.x, m3.b.x, m3.c.x);
	printf("%f %f %f", m3.a.y, m3.b.y, m3.c.y);
	printf("%f %f %f", m3.a.z, m3.b.z, m3.c.z);

	Matrix m4 = MatSub(m3, m1);
	printf("%f %f %f", m4.a.x, m4.b.x, m4.c.x);
	printf("%f %f %f", m4.a.y, m4.b.y, m4.c.y);
	printf("%f %f %f", m4.a.z, m4.b.z, m4.c.z);

	fVector mv5 = transform(v1, m4);
	printf("%f", mv5.x);
	printf("%f", mv5.y);
	printf("%f", mv5.z);

	Matrix tm2 = transpose(m2);
	printf("%f %f %f", tm2.a.x, tm2.b.x, tm2.c.x);
	printf("%f %f %f", tm2.a.y, tm2.b.y, tm2.c.y);
	printf("%f %f %f", tm2.a.z, tm2.b.z, tm2.c.z);

	Matrix tm2bym2 = mat_mult(m2, tm2);
	printf("%f %f %f", tm2bym2.a.x, tm2bym2.b.x, tm2bym2.c.x);
	printf("%f %f %f", tm2bym2.a.y, tm2bym2.b.y, tm2bym2.c.y);
	printf("%f %f %f", tm2bym2.a.z, tm2bym2.b.z, tm2bym2.c.z);

	Matrix tm2bym2_2 = MatrixByMatrixTranspose(m2, m2);
	printf("%f %f %f", tm2bym2_2.a.x, tm2bym2_2.b.x, tm2bym2_2.c.x);
	printf("%f %f %f", tm2bym2_2.a.y, tm2bym2_2.b.y, tm2bym2_2.c.y);
	printf("%f %f %f", tm2bym2_2.a.z, tm2bym2_2.b.z, tm2bym2_2.c.z);

return 0;
}