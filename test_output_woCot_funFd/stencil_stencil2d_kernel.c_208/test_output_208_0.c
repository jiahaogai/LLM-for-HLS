#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
<<<<<<< HEAD
        idx = (256 + orig[i + ((-4 + k) % 256)]) * 256 + j + ((-4 + k) % 256);
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
=======
        idx = (256 + orig[i + ((k - 4) << 8)] - filter[k]) << 8 | j + (-4 + k);
        val += orig[idx] * filter[k];
      }
      sol[i << 8 | j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}