**Requirements:**
 - A[8192]
 - S[8192]
 - F[9]

**Pre Processor Macros:**
 - ACCEL_DIM_A {8}
 - ACCEL_DIM_B {8}
 - ACCEL_DIM_F {9}
 - ACCEL_DIM_ORIG {8192}
 - ACCEL_DIM_S {8192}
 - ACCEL_SIZE_A {2048}
 - ACCEL_SIZE_B {2048}
 - ACCEL_SIZE_F {72}
 - ACCEL_SIZE_ORIG {8192}
 - ACCEL_SIZE_S {8192}
 - ACCEL_ALIGN_A {1}
 - ACCEL_ALIGN_B {1}
 - ACCEL_ALIGN_F {1}
 - ACCEL_ALIGN_ORIG {1}
 - ACCEL_ALIGN_S {1}


**Parameters:**

  - `orig` Input array. (8192)

  - `sol` Output array. (8192)

  - `filter` Filter array. (9)








#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_a:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
  for (i = 0; i <= 7; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_b:
/* Standardize from: for(j = 0; j < 8; j++) {...} */
    for (j = 0; j <= 7; j++) {
      s = 0;
      loop_f:
      for (k = 0; k < 9; k++) {
        idx = (((8 * i) + j) * 8) + k;
        s += filter[k] * orig[idx];
      }
      sol[((8 * i) + j)] = s;
    }
  }
}