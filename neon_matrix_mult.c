//Load matrices into memory
vld1.32 {d16-d19}, [r1]! // firs teight elements of matrix A
vld1.32 {d20-d23}, [r1]! // Last eight elements of matrix A
vld1.32 {d0-d3}, [r1]! // First eight elements of matrix B
vld1.32 {d4-d7}, [r1]! // Last eight elements of matrix B

vmul.f32 q12, q8, d0[0]
vmla.f32 q12, q9, d0[1]
vmla.f32 q12, q10, d1[0]
vmla.f32 q12, q11, d1[1]
