#include <arm_neon.h>
#include <stdio.h>
//#include "vector.h" only if we change the definition 
// I don't even know if this is at all useful...

//Vector (this is already in linear_ops.h actually...)
/*
typedef struct _fVector {
		float x;
		float y;
		float z; 
		float w;
	} fVector;
	*/
/*
//Matrix
typedef struct _Matrix{
	fVector a;
	fVector b;
	fVector c;
} Matrix;
*/
float32x4_t fVector_wrapper(fVector vector){
	float32x4_t neon_vec = vld1q_f32((float*)(&vector)); // ARM Neon Intrinsic to load a vect.
	return neon_vec;
}

fVector float32_to_fvector(float32x4_t f32){
    fVector result = {};
    float* retfl = (float*)(&result);
    retfl[0] = vgetq_lane_f32(f32, 0);
    retfl[1] = vgetq_lane_f32(f32, 1);
    retfl[2] = vgetq_lane_f32(f32, 2);
    retfl[3] = vgetq_lane_f32(f32, 3);
    return result;
}
/*
float Matrix_wrapper(Matrix matrix){ //im falling asleep 
	// Code goes here.
	float neon_mat[3];

	float32x4_t col1 = fVector_wrapper(matrix.a);
	float32x4_t col2 = fVector_wrapper(matrix.b);
	float32x4_t col3 = fVector_wrapper(matrix.c);

	neon_mat[0] = col1;
	neon_mat[1] = col2;
	neon_mat[2] = col3;
	
	return neon_mat;
}
*/

/*
//testing 
int main(){
	//Test Wrapped Vect
	fVector vector1 = {.x = 3.12, .y = 420.69, .z = 1337.420};

	float32x4_t neon_vector = fVector_wrapper(vector1);
    
    fVector vector2 = {};
    vector2=float32_to_fvector(neon_vector);
    
    fVector v4 = {.x = 130.234, .y = 2.4, .z = 8.25};
	fVector v5 = {.x = 234, .y = 1.7, .z = 9.25};
	fVector v6 = {.x = 224, .y = 5.234, .z = 12.25};

    Matrix matrix1 = {.a = v4, .b = v5, .c = v6};
    float32x4_t neon_matrix = Matrix_wrapper(matrix1);

    float* v2fl = (float*)(&vector2);
    int i;
	//Test if conversion worked by printing entries 
    for (i=0; i<=3; i++){
		printf("The %d entry is: %f\n", i, neon_vector[i]);
	}

	for (i=0; i<=2; i++){
		printf("The %d column is: %f\n", i, neon_matrix[i]);
	}
return 0;
}
*/