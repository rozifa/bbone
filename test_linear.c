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

	print_assess(time_taken, time_taken2);

//--------------- STRUCT MULTIPLICATION -----------------------
	fVector test_boy3 = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy4 = {.x = 2.01, .y = 3.44, .z = 5.6324};

	int k = 0;

	clock_t t3;
	t3 = clock();

	while (k <= trials){

		test_boy3 = VMult(test_boy3, test_boy4);

		k++;
	}

	t3 = clock() - t3;
	double time_taken3 = (((double)t3)/CLOCKS_PER_SEC);
	print_vector(test_boy3);
	printf("STRUCT Mult. took %f seconds.\n", time_taken3);



//----------------- NEON ELEMENTWISE MULTIPLICATION ------------------------
	fVector test_boy5 = {.x = 0.0001, .y = 0.013, .z = 0.0300202};
	fVector test_boy6 = {.x = 2.01, .y = 3.44, .z = 5.6324};
	float32x4_t neon_boy3 = fVector_wrapper(test_boy5);
	float32x4_t neon_boy4 = fVector_wrapper(test_boy6);

	int l = 0;

	clock_t t4;
	t4 = clock();

	while (l <= trials){

		float32x4_t neon_boy3 = fVector_wrapper(test_boy5);
		neon_boy3 = vmulq_f32(neon_boy3, neon_boy4);

		l++;
	}

	t4 = clock() - t4; 
	double time_taken4 = (((double)t4)/CLOCKS_PER_SEC);
	fVector back_boy2 = float32_to_fvector(neon_boy3);
	print_vector(back_boy2);
	printf("NEON Mult. took %f seconds.\n", time_taken4);

	print_assess(time_taken3, time_taken4);

//---------------------- STRUCT MATRIX BY VECT (TRANS.) --------------

//----------Test -----
	fVector v1 = {.x = 37.0, .y = 25.69, .z = 73.0}; //arbitrary 
	fVector v2 = {.x = 2.0, .y = 15.15, .z = 36.63};
	fVector v3 = {.x = 93.93, .y = 16.0, .z = 7.0};
	Matrix mat_boy = {.a = v1, .b = v2, .c = v3};
	float32x4x4_t neon_mat_boy = Matrix_wrapper(mat_boy);
	lVector struct_mat_boy = float32x4x4_to_lVector(neon_mat_boy);

	lVector back_boy4 = float32x4x4_to_lVector(neon_mat_boy);
	print_lVector(back_boy4);

//------------------------Struct Cross Prod---------------------
	int dango = 0;

	clock_t t4_5;
	t4_5 = clock();
	while (dango <= trials){

		fVector crossy = VCross(v1, v2); 

		dango++;
	}
	t4_5 = clock() - t4_5;
	double time_taken4_5 = (((double)t4_5)/CLOCKS_PER_SEC);
	printf("***STRUCT Cross. took %f seconds.\n", time_taken4_5);

//-----------------------Neon Cross Prod ------------------------
	int dingo = 0;

	float32x4_t w1 = fVector_wrapper(v1);
	float32x4_t w2 = fVector_wrapper(v2);

	float32_t* returner1[3];
	float* big = (float*)(&returner1);
	big[0] = vgetq_lane_f32(w1, 0);
	big[1] = vgetq_lane_f32(w1, 1);
	big[2] = vgetq_lane_f32(w1, 2);

	float32_t* returner2[3];
	float* boy = (float*)(&returner2);
	boy[0] = vgetq_lane_f32(w2, 0);
	boy[1] = vgetq_lane_f32(w2, 1);
	boy[2] = vgetq_lane_f32(w2, 2);
	float32_t* cross_product;

	clock_t t5;
	t5 = clock();
	while (dingo <= trials){
		float32x4_t dinger = intrinsic_cross_prod(cross_product, big, boy); 
		dingo++;
	}

	t5 = clock() - t5;
	double time_taken5 = (((double)t5)/CLOCKS_PER_SEC);
	printf("NEON Intr. Cross. took %f seconds.\n", time_taken5);

	fVector back_w1_check = float32_to_fvector(w1);
	fVector back_w2_check = float32_to_fvector(w2);

	print_vector(back_w1_check);
	print_vector(back_w2_check);

	
	//fVector back_dinger = float32_to_fvector(dinger);

	//print_vector(back_dinger);

//----------------------- NEON Assembly Cross Prod--------------------

	float const* test_returner1[3];
	float* test_big = (float*)(&test_returner1);
	test_big[0] = vgetq_lane_f32(w1, 0);
	test_big[1] = vgetq_lane_f32(w1, 1);
	test_big[2] = vgetq_lane_f32(w1, 2);

	float const* test_returner2[3];
	float* testy_boy = (float*)(&test_returner2);
	testy_boy[0] = vgetq_lane_f32(w2, 0);
	testy_boy[1] = vgetq_lane_f32(w2, 1);
	testy_boy[2] = vgetq_lane_f32(w2, 2);
	
	float* test_cross_product;

	int darno = 0;

	clock_t t6;
	t6 = clock();
	while (darno <= trials){
	//neon_assembly_cross(test_big, testy_boy, test_cross_product);
		float32x4_t assigner_boy = neon_assembly_cross(w1, w2);
		darno++;
	}
	t6 = clock() - t6;
	double time_taken6 = (((double)t6)/CLOCKS_PER_SEC);
	printf("***NEON Ass. Cross. took %f seconds.\n", time_taken6);


//----------------------- NEON MATRIX BY VECT (TRANS.) ---------------
/*
	Matrix mat_boy =  {.a = v1, .b = v2, .c = v3};
	fVector test_boy7 = {.x = 0.0031, .y = 0.0044, .z = 0.0010304};
	float32x4_t neon_mat_boy = //fMatrix_wrapper(mat_boy)...;
	float32x4_t neon_test_boy = fVector_wrapper(test_boy7);

	int d = 0;

	clock_t t6;
	t6 = clock();

	while (d <= trials){
		//neon mat boy not yet defined...
		float32x4_t trans_boy = neon_transform(neon_mat_boy, neon_test_boy7);

		d++;
	}

	t6 = clock() - t6;
	double time_taken5 = (((double)t6)/CLOCKS_PER_SEC);
	fVector backboy_3 = float32_to_fvector(neon_boy5);
	print_vector(backboy_3);
	printf("NEON Trans. took %f seconds. \n", time_taken5);

	print_assess() */

return 0;
}



//-----------------Test Trash ----------------------
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