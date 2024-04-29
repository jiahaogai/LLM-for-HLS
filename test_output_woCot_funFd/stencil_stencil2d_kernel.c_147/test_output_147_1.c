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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
      for (k = -4; k < 5; k++) {
        int cur;
        int flt;
        cur = orig[i * 64 + j * 8 + k + pad];
        flt = filter[4 + k];
        t += cur * flt;
      }
      sol[i * 64 + j + pad] = t;
=======
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i * 8 + j * 8 + pad * 8 + k - 4];
      }
      sol[i * 8 + j * 8 + pad * 8] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
<<<<<<< HEAD
      int t;
      t = sol[i * 64 + j + pad];
      orig[i * 64 + j + pad] = t;
=======
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        t += filter[k] * sol[i * 8 + j * 8 + pad * 8 + k - 4];
      }
      orig[i * 8 + j * 8 + pad * 8] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}