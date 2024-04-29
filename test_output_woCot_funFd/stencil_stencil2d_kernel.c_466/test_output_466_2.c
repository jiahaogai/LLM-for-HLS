<<<<<<< HEAD
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
=======
Code: ### Packing (non-kernel) function: 
#pragma ACCEL kernel

void pack_A(int A[8192],int pA[16384])
{
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[((i + pad) * (32 + 2 * 1) + (j + pad)) * (1) + k];
      }
      sol[i * (32 + 2 * 1) + j] = t;
=======
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 32; j++) {
      pA[(i * 32) + j] = A[(i * 32) + j];
    }
  }
}
#pragma ACCEL kernel

void pack_B(int B[8192],int pB[16384])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 32; j++) {
      pB[((i * 32) + j) * 2] = B[i * 32 + j];
      pB[((i * 32) + j) * 2 + 1] = 0;
    }
  }
}
#pragma ACCEL kernel

void unpack_P(int P[16384],int pP[8192])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      pP[(i * 32) + j] = P[(i * 32) + j];
    }
  }
}
#pragma ACCEL kernel

void unpack_A(int A[8192],int pA[16384])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      A[(i * 32) + j] = pA[(i * 32) + j];
    }
  }
}
#pragma ACCEL kernel

void unpack_B(int B[8192],int pB[16384])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 32; j++) {
      B[(i * 32) + j] = pB[((i * 32) + j) * 2];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}