#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int idy;
  int ftidx;
  int ftidy;
  int t;
=======
  int s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ftidx = -(4 + k);
        ftidy = -(4 + k);
        idx = i + ftidx;
        idy = j + ftidy;
        if (idx >= 0 && idx < 256 && idy >= 0 && idy < 256) {
          t += filter[k] * orig[idx * 256 + idy];
        }
      }
      sol[i * 256 + j] = t;
=======
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (i + ((0 - (4 + 1)) + (k / 3))) * 256 + j + ((k % 3) - 1);
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 256 + j] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}