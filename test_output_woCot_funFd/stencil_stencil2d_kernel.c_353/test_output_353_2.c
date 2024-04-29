#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{2}
=======
#pragma ACCEL TILE FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -4 + pad; k < 5 - pad; k++) {
        t += filter[4 + k] * orig[i * 64 + (j * 8 + k)];
      }
      sol[i * 64 + j * 8] = t;
=======
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        t += filter[((k + 4) < 0 ? (-(k + 4)) : (4 + k)) + 4] * orig[pad + ((i + k) << 3) + j];
      }
      sol[pad + ((i << 3) + j)] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{flatten}
=======
#pragma ACCEL PIPELINE auto{off}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      t = 0;
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4 + pad; k < 5 - pad; k++) {
        t += filter[4 + k] * sol[i * 64 + (j * 8 + k)];
      }
      orig[i * 64 + j * 8] = t;
=======
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        t += filter[((k + 4) < 0 ? (-(k + 4)) : (4 + k)) + 4] * sol[pad + ((j + k) << 3) + i];
      }
      sol[pad + ((i << 3) + j)] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}