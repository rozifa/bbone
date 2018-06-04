#include <arm_neon.h> // Arm neon SIMD functions for fast computation

// vld1.32 is the machine code that corrosponds to:
vld1q_f32(void); // in C. Loads a vect into memory