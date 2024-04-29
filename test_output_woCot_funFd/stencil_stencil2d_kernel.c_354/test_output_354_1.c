#pragma ACCEL kernel stencil

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int pt = 4;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    t = 0;
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + (j - 4) + 8192 * (j / 32 - pt)];
    }
    sol[i] = t;
=======
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 8 - 1) * (256 + 8 - 1) * k + (256 + 8 - 1) * j + i;
        val += filter[k] * orig[idx];
      }
      sol[idx] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}