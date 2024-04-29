#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int x;
  int y;
=======
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
<<<<<<< HEAD
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        x = i - 4 + k / 5;
        y = j - 4 + k % 5;
        t += filter[k] * orig[x * 8192 + y];
      }
      sol[i * 8192 + j] = t;
=======
      result = ((orig[i * 8192 + j] + orig[i * 8192 + j + 1] + orig[i * 8192 + j + 8192] + orig[i * 8192 + j + 8191] + orig[
                  (i + 1) * 8192 + j] + orig[((i + 1) * 8192) + j + 1] + orig[((i + 1) * 8192) + j + 8192] + orig[((i + 
                  1) * 8192) + j + 8191]) / 8);
      sol[i * 8192 + j] = result;
    }
  }
/* Standardize from: for(i = 0; i < 8192; i++) {...} */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    blk:
    for (j = 0; j < 8; j++) {
      s:for(k = 0; k < 9; k++) {
        sol[i * 8192 + j * 64] += filter[k] * orig[i * 8192 + j * 64 + k];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}