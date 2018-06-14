#include <arm_neon.h>

//Various custom data types and linear algebra operations that can be done with them.
//Replace vectormath.c with all these bad boys...
//Data types
typedef struct _fVector{
	float x; 
	float y; 
	float z;
} fVector; 

typedef struct _sVector{
	float x;
	float y;
} sVector;

// Matrix

typedef struct _Matrix{
	fVector a;
	fVector b;
	fVector c;
} Matrix;

typedef struct _sMatrix{
	sVector a;
	sVector b;
} sMatrix;

//like a matrix...can convert back and forth 
//Just for a test... this needs to be changed / removed...
typedef struct _lVector{
	float a;
	float b;
	float c;
	float x;

	float d;
	float e;
	float f;
	float y;

	float g;
	float h;
	float i;
	float z;
} lVector; 

//My Operation Implementations:

// Elementwise Addition of Vectors
fVector VecAdd(fVector v1, fVector v2){
	fVector result = {.x = v1.x + v2.x , 
					  .y = v1.y + v2.y , 
					  .z = v1.z + v2.z};
	return result;
}
fVector VecSub(fVector v1, fVector v2){
	fVector result = {.x = v1.x - v2.x , 
					  .y = v1.y - v2.y , 
					  .z = v1.z - v2.z};
	return result;
	}

//Elementwise Addition of Matrices
Matrix MatAdd(Matrix m1, Matrix m2){
	Matrix result = {.a = VecAdd(m1.a, m2.a), 
					 .b = VecAdd(m1.b, m2.b), 
					 .c = VecAdd(m1.c, m2.c)};
	return result;
	}
	 
Matrix MatSub(Matrix m1, Matrix m2){
	Matrix result = {.a = VecSub(m1.a, m2.a), 
					 .b = VecSub(m1.b, m2.b), 
					 .c = VecSub(m1.c, m2.c)};
	return result;
	}

//Elementwise Multiplication of Vectors
fVector VMult(fVector v1, fVector v2){
	fVector result = {.x = v1.x + v2.x, 
					  .y = v1.y + v2.y, 
					  .z = v1.z + v2.z};
	return result;
}

//Constant Multiplication by Vector
fVector CMult(fVector v, float c){
	fVector result = {.x = v.x * c, 
					  .y = v.y * c, 
					  .z = v.z * c};
	return result;
}

// Dot Product

float VDot(fVector vector1, fVector vector2){
	float dot_product;

	dot_product = vector1.x * vector2.x +
				  vector1.y * vector2.y +
				  vector1.z * vector2.z;

	return dot_product;
}

// Cross Product

fVector VCross(fVector vec1, fVector vec2){
	fVector cross_prod;

	cross_prod.x = vec1.y * vec2.z - vec1.z * vec2.y;
	cross_prod.y = vec1.z * vec2.y - vec1.x * vec2.z;
	cross_prod.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return cross_prod;
}

// Apply a transformation defined by a matrix (left mult.)

fVector transform(fVector v, Matrix m){
	fVector transformed;
	transformed.x = m.a.x*v.x + m.a.y*v.y + m.a.z*v.z;
	transformed.y = m.b.x*v.x + m.b.y*v.y + m.b.z*v.z;
	transformed.z = m.c.x*v.x + m.c.y*v.y + m.c.z*v.z;
	return transformed;
}

float32x4_t neon_transform(float32x4_t * matrix, float32x4_t vector){
	float32x4_t result;

  	result = vmulq_f32(matrix[0], vector); //multiply
  	result = vmlaq_f32(result, matrix[1], vector); //multiply + accumulate
  	result = vmlaq_f32(result, matrix[2], vector);
  	result = vmlaq_f32(result, matrix[3], vector);

  	return result;
}

// Transpose a Matrix
Matrix transpose(Matrix m){
	Matrix transposed;
	fVector v1 = {.x = m.a.x, .y = m.b.x, .z = m.c.x};
	fVector v2 = {.x = m.a.y, .y = m.b.y, .z = m.c.y};
	fVector v3 = {.x = m.a.z, .y = m.b.z, .z = m.c.z};
	transposed.a = v1;
	transposed.b = v2;
	transposed.c = v3;

	return transposed;
}

// Def Mat. Mult. via cross prods. 

Matrix mat_mult(Matrix m1, Matrix m2){
	Matrix result;
	m1 = transpose(m1); // use a pointer instead?
	result.a.x = VDot(m1.a, m2.a); result.a.y = VDot(m1.a, m2.b); result.a.z = VDot(m1.a, m2.c);
	result.b.x = VDot(m1.b, m2.a); result.b.y = VDot(m1.b, m2.b); result.b.z = VDot(m1.b, m2.c);
	result.c.x = VDot(m1.c, m2.a); result.c.y = VDot(m1.c, m2.b); result.c.z = VDot(m1.c, m2.c);

	return result;
}
// The following lines improve code in the original Snic code. 
// Replace lines 171-188 in rotary.c
Matrix MatrixByMatrixTranspose(Matrix m1, Matrix m2){
	Matrix m2_tranp = transpose(m2);
	Matrix result = mat_mult(m1, m2_tranp);

	return result;
}
// Replace lines 245-263 in rotary.c
Matrix MatrixTransposeByMatrix(Matrix m1, Matrix m2){
	Matrix m1_tranp = transpose(m1);
	Matrix result = mat_mult(m1_tranp, m2);

	return result;
}

//Cofactor type, contains 3 2x2 matrices
typedef struct _Cofactor{
	sMatrix one; // cofactor matrices are 2 x 2 for a 3 x 3 matrix. 
	sMatrix two;
	sMatrix three;
} Cofactor;

//Returns the cofactor matrices of a 3x3 matrix
Cofactor cofactor(Matrix m){
	Cofactor result = {.one   = {.a.x = m.b.y, .a.y = m.b.z, 
								 .b.x = m.c.y, .b.y = m.c.z},
					   .two   = {.a.x = m.a.y, .a.y = m.a.z,
					   			 .b.x = m.c.y, .b.y = m.c.z},
					   .three = {.a.x = m.a.y, .a.y = m.a.z, 
					   			 .b.x = m.b.y, .b.y = m.b.z}};

	return result;
}

//Compute the determinent of a 3x3 matrix via use of the cofactors
float determinant(Matrix m){
	float result;

	Cofactor cofacs = cofactor(m);
	float cross_1 = cofacs.one.a.x * cofacs.one.b.y - cofacs.one.a.y * cofacs.one.b.x;
	float cross_2 = cofacs.two.a.x * cofacs.two.b.y - cofacs.two.a.y * cofacs.two.b.x;
	float cross_3 = cofacs.three.a.x * cofacs.three.b.y - cofacs.three.a.y * cofacs.three.b.x;

	float term_1 = m.a.x * cross_1;
	float term_2 = m.b.x * cross_2;
	float term_3 = m.c.x * cross_3;

	result = term_1 - term_2 + term_3;

	return result;
}

//Array wrapper
float* fVecTOarray(fVector vector){

	static float converted[3];

	converted[0] = vector.x;
	converted[1] = vector.y;
	converted[2] = vector.z;

	return converted;
}

//------------ Mat. Mult. Assembly --------------------------------
// We can move these NEON operations to a seperate file from the struct operations perhaps

inline __attribute__((always_inline)) void neon_assembly_natmul() {
	register type name asm("register") = assignment; //template
	register type name asm("register") = assignment;
	register type name asm("register") = assignment;

	asm volatile (
	// Load both matrices into NEON registers
	"vld1.32	{d16-d19}, {r1}! \n" // Matrix 1 change from curly to square?
	"vld1.32	{d20-d23}, [r1]! \n"
	"vld1.32 	{d0-d3}, [r2]! \n" //Matrix 2
	"vld1.32 	{d4-d7}, {r2}! \n" 

	//One Column of results
	"vmul.f32	q12, q8, d0[0] \n"
	"vmla.f32 	q12, q9, d0[1] \n"
	"vmla.f32 	q12, q10, d1[0] \n" 
	"vmla.f32 	q12, q11, d1[1] \n"

	//macro
	".macro mul_col_f32 res_q, col0_d, col1_d \n"
	"vmul.f32 \res_q, q8, \col0_d[0] \n"
	"vmla.f32 \res_q, q9, \col0_d[1] \n"
	"vmla.f32 \res_q, q10, \col1_d[0] \n"
	"vmla.f32 \res_q, q11, \col1_d[1] \n"


	//implement matrix by matrix using our macros (less code)

	//load elements
	"vld1.32	{d16-d19}, {r1}! \n" // Matrix 1
	"vld1.32	{d20-d23}, [r1]! \n"
	"vld1.32 	{d0-d3}, [r2]! \n" //Matrix 2
	"vld1.32 	{d4-d7}, {r2}! \n" 

	//multiplication via macro
	"mul_col_f32 q12, d0, d1 \n"
	"mul_col_f32 q13, d2, d3 \n"
	"mul_col_f32 q14, d4, d5 \n"
	"mul_col_f32 q15, d6, d7 \n"

	//store results
	"vst1.32 	{d24-d27}, {r0}! \n"
	"vst1.32 	{d28-d31}, {r0}! \n"
	);
}


//Cross product using inline assembly
//Maybe someone else can implement this EVEN faster by interleaving the vectors using vst3.... I coudlnt get it to work
inline __attribute__((always_inline)) float32x4_t neon_assembly_cross(float32x4_t a, float32x4_t b) {
    register float32x4_t vector_1 asm("q0") = a;
    register float32x4_t vector_2 asm("q2") = b;
    register float32x4_t cross_product asm("q8");
    //ok, now...I go nutty
    asm volatile(
        "vmov    q1, q0              \n\t"
        "vmov    q3, q2              \n\t"
        "vzip.32 q0, q1              \n\t" 
        "vzip.32 q2, q3              \n\t" 
        "vmul.f32 d16, d1, d6        \n\t" 
        "vmul.f32 d18, d3, d4        \n\t" 
        "vmul.f32 d17, d0, d5        \n\t" 
        "vmls.f32 d16, d3, d5        \n\t" 
        "vmls.f32 d18, d0, d6        \n\t" 
        "vmls.f32 d17, d1, d4        \n\t" 
        "vuzp.32 d16, d18"                 
        : "=w" (vector_1), "=w" (vector_2), "=w" (cross_product)
        : "0" (vector_1), "1" (vector_2)
        : "q1", "q3", "q9"
    );

    return cross_product;
}


//Cross Product Using C-Intrinsics - a X b - store in r
float32x4_t intrinsic_cross_prod(float32_t *r, float32_t* a, float32_t* b){
	
	//Load vector elements into NEON registers
	float32x2_t vector_a_1 = vld1_f32(a + 1);
	float32x2_t vector_a_2 = vld1_f32(a);
	float32x2_t vector_b_1 = vld1_f32(b + 1);
	float32x2_t vector_b_2 = vld1_f32(b);

	//Transformations for the calculations
	float32x4_t vector_a = vcombine_f32(vector_a_1, vector_a_2);
	float32x4_t vector_b = vcombine_f32(vector_b_1, vector_b_2);
	float32x4_t vector_a_rot = vextq_f32(vector_a, vector_a, 1);
	float32x4_t vector_b_rot = vextq_f32(vector_b, vector_b, 1);

	//Perform the calculation
	float32x4_t product = vmulq_f32(vector_a, vector_b_rot);
	product = vmlsq_f32(product, vector_a_rot, vector_b);

	return product;

	//Store the results - if use this method, change type of f(x) to void
	//vst1_f32(r, vget_low_f32(product));
	//vst1_lane_f32(r + 2, vget_high_f32(product), 0);

	//Alternative storage
}

//Dot product using NEON C-intrinsics
void dot_prod(){

	//code goes here

}