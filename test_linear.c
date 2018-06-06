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
// ------------ STRUCT ADDING ---------------------------
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
	printf("STRUCT Add. took %f seconds.\n", time_taken);
// -------------- NEON ADDING ------------------------------------- 
	fVector test_boy = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy2 = {.x = 0.00101, .y = 0.000001, .z = 0.00001};
	//convert the above
	float32x4_t neon_boy = fVector_wrapper(test_boy);
	float32x4_t neon_boy2 = fVector_wrapper(test_boy2);
	
	int j = 0;
	
	clock_t t2;
	t2 = clock();

	while (j <= trials){
		
		float32x4_t neon_boy = fVector_wrapper(test_boy);
		neon_boy = vaddq_f32(neon_boy, neon_boy2);
		
		j++;

	}

	t2 = clock() - t2;
	double time_taken2 = (((double)t2)/CLOCKS_PER_SEC);
	fVector back_boy = float32_to_fvector(neon_boy);
	print_vector(back_boy);
	printf("NEON Add. took %f seconds.\n", time_taken2); 

//--------------- STRUCT MULTIPLICATION -----------------------
	fVector test_boy3 = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy4 = {.x = 2.01, .y = 3.44, .z = 5.6324};

	int k = 0;

	clock_t t3;
	t3 = clock();

	while (k <= 1000001){

		test_boy3 = VMult(test_boy3, test_boy4);

		k++;
	}

	t3 = clock() - t3;
	double time_taken3 = (((double)t3)/CLOCKS_PER_SEC);
	print_vector(test_boy3);
	printf("STRUCT Mult. took %f seconds.\n", time_taken3);



//----------------- NEON MULTIPLICATION ------------------------
	fVector test_boy5 = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy6 = {.x = 2.01, .y = 3.44, .z = 5.6324};
	float32x4_t neon_boy3 = fVector_wrapper(test_boy5);
	float32x4_t neon_boy4 = fVector_wrapper(test_boy6);

	int l = 0;

	clock_t t4;
	t4 = clock();

	while (l <= 1000001){

		float32x4_t neon_boy3 = fVector_wrapper(test_boy5);
		neon_boy3 = vmulq_f32(neon_boy3, neon_boy4);

		l++;
	}

	t4 = clock() - t4; 
	double time_taken4 = (((double)t4)/CLOCKS_PER_SEC);
	fVector back_boy2 = float32_to_fvector(neon_boy3);
	print_vector(back_boy2);
	printf("NEON Mult. took %f seconds.\n", time_taken4);

return 0;
}

// Working on this code...
// --------------------------------------------------------
/*	//vmulq_f32() NEON Multiplication.
	fVector v1 = {.x = 37.0, .y = 25.69, .z = 73.0}; //arbitrary 
	fVector v2 = {.x = 2.0, .y = 15.15, .z = 36.63};
	fVector v3 = {.x = 93.93, .y = 16.0, .z = 7.0};

	fVector v4 = {.x = 130.234, .y = 2.4, .z = 8.25};

	//Convert to neon
	float32x4_t c1 = fVector_wrapper(v1);
	float32x4_t c2 = fVector_wrapper(v2);
	float32x4_t c3 = fVector_wrapper(v3);
	float32x4_t c_vec = fVector_wrapper(v4);  */
//---------------------------------------------------------------	


/*
	static __always_inline float32x2_t dotProduct(float32x4x2_t input1, float32x4x2_t input2)
{
    float32x2_t d0, d1;
    float32x4_t q0;
    input1.val[0] = vmulq_f32(input1.val[0], input2.val[0]);
    input1.val[1] = vmulq_f32(input1.val[1], input2.val[1]);

    q0 = vaddq_f32(input1.val[0], input1.val[1]);
    d0 = vget_low_f32(q0);
    d1 = vget_high_f32(q0);
    d0 = vpadd_f32(d0, d1);
    d0 = vpadd_f32(d0, d1);
    return d0;
}

void matMulF_neon(float *pDst, float *pMatA, float *pMatB)
{
    float32x4x4_t   line01, line23, line45, line67;
    float32x4x2_t   b[8], *pA, *pB, temp;
    float32x2x4_t   result;
    uint32_t        i;

    // vld4 for easier transpose
    line01 = vld4q_f32(pMatB++);
    line23 = vld4q_f32(pMatB++);
    line45 = vld4q_f32(pMatB++);
    line67 = vld4q_f32(pMatB);

    // transpose MatB
    vuzpq_f32(line01.val[0], line45.val[0]);
    vuzpq_f32(line01.val[1], line45.val[1]);
    vuzpq_f32(line01.val[2], line45.val[2]);
    vuzpq_f32(line01.val[3], line45.val[3]);

    vuzpq_f32(line23.val[0], line67.val[0]);
    vuzpq_f32(line23.val[1], line67.val[1]);
    vuzpq_f32(line23.val[2], line67.val[2]);
    vuzpq_f32(line23.val[3], line67.val[3]);

    // store MatB to stack
    b[0].val[0] = line01.val[0];
    b[0].val[1] = line01.val[1];
    b[1].val[0] = line01.val[2];
    b[1].val[1] = line01.val[3];
    b[2].val[0] = line23.val[0];
    b[2].val[1] = line23.val[1];
    b[3].val[0] = line23.val[2];
    b[3].val[1] = line23.val[3];

    b[4].val[0] = line45.val[0];
    b[4].val[1] = line45.val[1];
    b[5].val[0] = line45.val[2];
    b[5].val[1] = line45.val[3];
    b[6].val[0] = line67.val[0];
    b[6].val[1] = line67.val[1];
    b[7].val[0] = line67.val[2];
    b[7].val[1] = line67.val[3];

    pA = (float32x4x2_t *) pMatA;
    i = 8;
    do
    {
        // just the right amount of data for aarch32 NEON register bank size
        pB = b;
        temp = *pA++;
        result.val[0] = dotProduct(*pB++, temp);
        result.val[1] = dotProduct(*pB++, temp);
        result.val[2] = dotProduct(*pB++, temp);
        result.val[3] = dotProduct(*pB++, temp);
        vst4_lane_f32(pDst++, result, 0);

        result.val[0] = dotProduct(*pB++, temp);
        result.val[1] = dotProduct(*pB++, temp);
        result.val[2] = dotProduct(*pB++, temp);
        result.val[3] = dotProduct(*pB, temp);
        vst4_lane_f32(pDst++, result, 0);
    } while (--i);
}
*/