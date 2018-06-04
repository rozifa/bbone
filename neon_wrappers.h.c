#include <arm_neon.h>
#include <stdio.h>
//#include "vector.h" only if we change the definition 

typedef struct _fVector {
		float x;
		float y;
		float z; 
		float w;
	} fVector;

float32x4_t fVector_wrapper(fVector vector){
	float32x4_t neon_vec = vld1q_f32((float*)(&vector)); // ARM Neon Intrinsic to load a vect.
	return neon_vec;
}

int i;

fVector float32_to_fvector(float32x4_t f32){
    fVector ret = {};
    float* retfl = (float*)(&ret);
    retfl[0] = vgetq_lane_f32(f32, 0);
    retfl[1] = vgetq_lane_f32(f32, 1);
    retfl[2] = vgetq_lane_f32(f32, 2);
    retfl[3] = vgetq_lane_f32(f32, 3);
    return ret;
}

int main(){
	//Test Wrapped Vect
	fVector vector1 = {.x = 3.12, .y = 420.69, .z = 1337.420};
	float32x4_t neon_vector = fVector_wrapper(vector1);
    
    fVector vector2 = {};
    vector2=float32_to_fvector(neon_vector);

    float* v2fl = (float*)(&vector2);

	//Test if conversion worked by printing entries 
    for (i=0; i<=3; i++){
		printf("The %d entry is: %f\n", i, neon_vector[i]);
	}
return 0;
}

