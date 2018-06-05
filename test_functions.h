#include <stdio.h>

//These functions are to be used in test_linear.c to execute the enccassary tests

//print entries of a neon array 
fVector vector2 = {};
vector2 = float32_to_fvector(neon_vector1);

float* v2fl = (float*)(&vector2);
int i;
//Test if conversion worked by printing entries 
for (i = 0; i <= 3; i++){
printf("The %d entry is: %f\n", i, neon_vector1[i]);


