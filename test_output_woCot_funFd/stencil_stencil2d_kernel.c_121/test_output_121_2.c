#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
=======
  stencil_label1:
  for (i = 4096; i < 8192 - 4096; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = ((filter[0] * orig[i * 256 + j]) + (filter[1] * orig[i * 256 + j + 1]) + (filter[2] * orig[(i + 1) * 256 + j]) + (filter[3] * orig[(i + 1) * 256 + j + 1]) + (filter[4] * orig[(i + 2) * 256 + j]) + (filter[5] * orig[(i + 2) * 256 + j + 1]) + (filter[6] * orig[(i + 1) * 256 + j + 2]) + (filter[7] * orig[i * 256 + j + 2]) + (filter[8] * orig[(i - 1) * 256 + j + 2])) / 256;
      sol[i * 256 + j] = result;
=======
#pragma ACCEL PARALLEL FACTOR=auto{8}
    stencil_label2:
    for (j = 0; j < 64; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{8}
      stencil_label3:
      for (k = -4; k < 5; k++) {
        idx = i + k * 64;
        val += filter[k + 4] * orig[idx];
      }
      sol[i] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}