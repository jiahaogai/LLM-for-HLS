#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int t;
  int pt = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 0; i < 8192; i++) {
    t = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 8 - 1) * (k - 4) + (i - 4);
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + (j - 4) * 8192];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sol[i] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}