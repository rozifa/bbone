//Various custom data types and linear algebra operations that can be done with them.

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

	result = term_1 + term_2 + term_3;

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


/*
// This is all wrong...
//Maybe come back to this..was
float MatrixTOarray(Matrix matrix){
	float converted[3][3];
	float cols[3];

	col1 = fVecTOarray(matrix.a);
	col2 = fVecTOarray(matrix.b);
	col3 = fVecTOarray(matrix.c);
	
	cols[0] = col1;
	cols[1] = col2;
	cols[2] = col3;

	int i;
	int j;

	for (i=0; i<= 2; i++){
		for (j=0; j<= 2; j++){
			converted[i][j] = cols[j][i]
			// etc... 
		}
	}
	return converted;
}
*/
/* void arrayTOmatrix(float array){

	void result;

        int ;
        int ;
        int ;

        for (i=0; ){
        	 
        }

	return result;

} */