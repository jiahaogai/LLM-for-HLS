#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int val;
=======
  int center = 45;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((-4 + k) % 256)]) * 256 + j + ((-4 + k) % 256);
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
=======
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      idx = (8190 * (j - 1)) + i;
      sol[idx] = ((filter[0] * orig[idx - 8190 - 1]) + (filter[1] * orig[idx - 8190]) + (filter[2] * orig[idx - 8190 + 1]) + (filter[3] * orig[idx - 1]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 1]) + (filter[6] * orig[idx + 8190 - 1]) + (filter[7] * orig[idx + 8190]) + (filter[8] * orig[idx + 8190 + 1])) / 40.0;
/* Standardize from: ((0.015 * orig[idx - 8190 - 1]) + (0.060 * orig[idx - 8190]) + (0.015 * orig[idx - 8190 + 1]) + (0.060 * orig[idx - 1]) + (0.200 * orig[idx]) + (0.060 * orig[idx + 1]) + (0.015 * orig[idx + 8190 - 1]) + (0.060 * orig[idx + 8190]) + (0.015 * orig[idx + 8190 + 1])) / 40.0; */
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}