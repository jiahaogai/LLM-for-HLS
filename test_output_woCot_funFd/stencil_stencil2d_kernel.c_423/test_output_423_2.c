#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = ((filter[j * 8 + k] * orig[i * 8 + k]) << 3) + result;
      }
      sol[i * 8 + j] = result;
      result = 0;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((orig[8192 * (0 + (i - 1)) + (0 + (j - 1))] * filter[0]) + (orig[8192 * (0 + (i - 1)) + (1 + (j - 1))] * filter[1]) + (orig[8192 * (0 + (i - 1)) + (2 + (j - 1))] * filter[2]) + (orig[8192 * (1 + (i - 1)) + (0 + (j - 1))] * filter[3]) + (orig[8192 * (1 + (i - 1)) + (1 + (j - 1))] * filter[4]) + (orig[8192 * (1 + (i - 1)) + (2 + (j - 1))] * filter[5]) + (orig[8192 * (2 + (i - 1)) + (0 + (j - 1))] * filter[6]) + (orig[8192 * (2 + (i - 1)) + (1 + (j - 1))] * filter[7]) + (orig[8192 * (2 + (i - 1)) + (2 + (j - 1))] * filter[8])) / 8192;
      sol[8192 * (i) + (j)] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}