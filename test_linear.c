#include <stdio.h>
// #include "linear_ops.h"
#include <arm_neon.h>
#include "linear_ops.h"
#include "neon_wrappers.h" // have to include the .c as a .h 

//Initalize test vectors
fVector v1 = {.x = 3.5, .y = 3.14, .z = 69.420}; //arbitrary 
fVector v2 = {.x = 1337.69, .y = 10, .z = 96.2};
fVector v3 = {.x = 220.234, .y = 1.234, .z = 1998.25};

fVector v4 = {.x = 130.234, .y = 2.4, .z = 8.25};
fVector v5 = {.x = 234, .y = 1.7, .z = 9.25};
fVector v6 = {.x = 224, .y = 5.234, .z = 12.25};

//Initilize test matrices
Matrix m1 = {.a = v1, .b = v2, .c = v3};
Matrix m2 = {.a = v4, .b = v5, .c = v6};

//Neonize the vects
float32x4_t neon_vector1 = fVector_wrapper(v1);
float32x4_t neon_vector2 = fVector_wrapper(v2);
float32x4_t neon_vector3 = fVector_wrapper(v3);

float32x4_t neon_vector4 = fVector_wrapper(v4);
float32x4_t neon_vector5 = fVector_wrapper(v5);
float32x4_t neon_vector6 = fVector_wrapper(v6);

int main(){
    fVector vector2 = {};
    vector2=float32_to_fvector(neon_vector1);

    float* v2fl = (float*)(&vector2);
    int i = 0;
	//Test if conversion worked by printing entries 
    for (i = 0; i <= 3; i++){
		printf("The %d entry is: %f\n", i, neon_vector1[i]);
	}
return 0;
}