#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      val = ((orig[i] << 6) + filter[0]) + ((orig[i + 1] << 5) + filter[1]) + ((orig[i + 32] << 2) + filter[2]) + ((orig[i + 33] >> 2) + filter[3]) + ((orig[i + 32 + 1] >> 6) + filter[4]);
      sol[i] = val;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i * 8192 + j] * filter[0]) + (orig[i * 8192 + j + 1] * filter[1]) + (orig[i * 8192 + j + 8192] * filter[2]) + (orig[(i + 1) * 8192 + j] * filter[3]) + (orig[(i + 1) * 8192 + j + 1] * filter[4]) + (orig[(i + 1) * 8192 + j + 8192] * filter[5]) + (orig[(i - 1) * 8192 + j] * filter[6]) + (orig[(i - 1) * 8192 + j + 1] * filter[7]) + (orig[(i - 1) * 8192 + j + 8192] * filter[8])) / 4192.0;
      sol[i * 8192 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}