#include "filename.extension" // imports a file or library

// Defining a function

return_type function_name(parameter_list) {
	body of the function 
	return result
}

//Ex

int max(int number1, int number2) {
	int result;

	if (number1 > number2)
		result = number1;
	else if (number1 < number2)
		result = number2;
	else
		result = number1;
	return result;
}

// calling the function
int ret;
int a = 420 // Can initilize vars without values
int b = 69 // even though max returns an int we still have to def int for ret
ret = max(a, b)

// Data types

type arrayName [array_size]; // Declare an array

double numbers [10]; //List of 10 doubles
double others [4] = {1.23, 3.45, 2.34, 6.45} //Explicit

// Write to numbers

for (int i = 0; i<=10; i++) {
	numbers[i] = i + 42;
}

// Loops

for (init; condition; increment) {
	logic;
}

for (;;) {
	printf("Infinite loop is running. \n");
}

int counter = 0
while (counter <=10){
	printf("Counter value is %d\n", counter);
	counter++;
}

// Structures (kind of like a very primitive object)
struct tag {
	member def;
	member def;
	...
	member def;
} [structure variables];

struct Book {
	char title[50];
	char author[50];
	char subject[100];
	int book_id;
};
//This is like making our own, new type (like an int or char)
typedef struct _fVecotr {
	float x;
	float y;
	float z;
} fVecotr; //Now instead of calling "struct ..., we just call fVec."

// Making vects and a mat

fVector vec1 = {.x=0.035,.y=0.0034,.z=0.0324}
fVector vec2 = {.x=0.025,.y=0.0024,.z=0.0624}
fVector vec3 = {.x=0.055,.y=0.0034,.z=0.1344}
Matrix mat = {.a=vec1,.b=vec2.c=vec3}
//Indexing the matrix
// mat.a.x = 0.035, mat.b.y = 0.0024, mat.c.z = 0.1344

// Two ways to populate the struct
struct Book BookB = {.title="title", .author="man", 
					.subject="Mystery", .book_id=1337};

struct Book BookA;
BookA.title = "Title of the Book";
BookA.book_id =  35;
BookA.author = "Big Boy"
BookA.subject = "Fiction"

// Pointers
int var1;
printf("The memory address for var1 is: %x\n", &var1) // access mem ad with &

type *pointer-name;
int var = 20
int *vp = NULL;
vp = &var; // now vp has the memory address value of var

// Data Types
