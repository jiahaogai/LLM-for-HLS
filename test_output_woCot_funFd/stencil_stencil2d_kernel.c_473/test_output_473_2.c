<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
- Arrays are passed by reference for efficiency (`orig`, `sol`); passing by value would require copying the data into the kernel's memory.
 
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int pad;
  pad = 1;
=======
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4 + pad; k < 4 + pad; k++) {
        if ((k < -pad) || (k > 7)) {
          t += orig[i + k] * filter[0];
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        else {
          t += orig[i + k] * filter[4 + k];
        }
      }
      sol[i * 8192 + j] = t;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1,j]) + (0 * orig[i,j - 1]) + (1 * orig[i,j]) + (0 * orig[i,j + 1]) + (0 * orig[i + 1,j])) + filter[4];
      sol[i,j] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      orig[i,j] = sol[i,j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}