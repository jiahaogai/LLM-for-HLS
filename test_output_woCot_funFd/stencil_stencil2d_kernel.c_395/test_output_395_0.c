#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      result = ((0 + filter[0]) * orig[i * 256 + j]) + ((0 + filter[1]) * orig[i * 256 + j + 1]) + ((0 + filter[2]) * orig[(i + 1) * 256 + j]) + ((0 + filter[3]) * orig[(i + 1) * 256 + j + 1]) + ((0 + filter[4]) * orig[(i + 2) * 256 + j]) + ((0 + filter[5]) * orig[(i + 2) * 256 + j + 1]) + ((0 + filter[6]) * orig[(i + 3) * 256 + j]) + ((0 + filter[7]) * orig[(i + 3) * 256 + j + 1]) + ((0 + filter[8]) * orig[(i + 4) * 256 + j]);
=======
      result = ((filter[0] * orig[i * 256 + j]) + (filter[1] * orig[i * 256 + j + 1]) + (filter[2] * orig[(i + 1) * 256 + j]) + (filter[3] * orig[(i + 1) * 256 + j + 1]) + (filter[4] * orig[(i + 2) * 256 + j]) + (filter[5] * orig[(i + 2) * 256 + j + 1]) + (filter[6] * orig[(i + 1) * 256 + j - 1]) + (filter[7] * orig[i * 256 + j - 1]) + (filter[8] * orig[(i - 1) * 256 + j - 1]) + (filter[9] * orig[(i - 1) * 256 + j]) + (filter[10] * orig[(i - 1) * 256 + j + 1]) + (filter[11] * orig[(i - 2) * 256 + j + 1]) + (filter[12] * orig[(i - 2) * 256 + j]) + (filter[13] * orig[(i - 2) * 256 + j - 1]));
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      sol[i * 256 + j] = result;
    }
  }
}