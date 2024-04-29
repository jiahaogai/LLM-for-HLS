#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int r;
  int c;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (r = 2; r < 128 - 1; r++) {
=======
  outer:
  for (i = 0; i < 128 + 2; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    for (c = 2; c < 64 - 1; c++) {
      i = r * 64 + c;
      sol[i] = filter[0] * orig[i] + filter[1] * (orig[i - 1] + orig[i + 1]) + filter[2] * orig[i - 64] + filter[3] * (orig[i - 65] + orig[i + 64]) + filter[4] * (orig[i - 128] + orig[i + 128]) + filter[5] * (orig[i - 129] + orig[i + 127]) + filter[6] * orig[i - 2] + filter[7] * (orig[i - 3] + orig[i + 2]) + filter[8] * orig[i - 127] + filter[9] * (orig[i - 129] + orig[i + 127]);
=======
    middle:
    for (j = 0; j < 128 + 2; j++) {
      idx = (i - 1) * (128 + 2) + j - 1;
      val = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * orig[idx + 2]) + (filter[3] * (orig[idx + 1 + 1] + orig[idx - 1 - 1])) + (filter[4] * (orig[idx + 2 + 1] + orig[idx - 2 - 1])) + (filter[5] * (orig[idx + 1 + 2] + orig[idx - 1 - 2])) + (filter[6] * (orig[idx + 2 + 2] + orig[idx - 2 - 2])) + (filter[7] * orig[idx + 2 + 2 + 1])) >> 15;
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}