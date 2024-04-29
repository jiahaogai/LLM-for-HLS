<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 void stencil(int orig[8192],int sol[8192],int filter[9])
=======
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Do not execute the `stencil` kernel concurrently to avoid excessive resource consumption.

#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int idy;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
=======
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
<<<<<<< HEAD
      t = 0;
      idx = (i - 1) * 128 + j - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idy = k / 3 - 1;
        t += filter[k] * orig[idx + idy * 128];
      }
      sol[idx] = t;
=======
      idx = i * 128 + j;
      val = orig[idx] + filter[0] * orig[idx - 128] + filter[1] * orig[idx - 1] + filter[2] * orig[idx + 1] + filter[3] * orig[idx + 128] + filter[4] * orig[idx - 1 - 128] + filter[5] * orig[idx - 128 - 1] + filter[6] * orig[idx + 1 - 128] + filter[7] * orig[idx + 128 - 1] + filter[8] * orig[idx - 128];
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}