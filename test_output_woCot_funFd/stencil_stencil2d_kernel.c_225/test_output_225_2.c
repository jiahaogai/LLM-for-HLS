<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i * 8 + j] + orig[i * 8 + j + 1] + orig[i * 8 + j + 8] + orig[i * 8 + j - 1] + orig[i * 8 + j - 8] + orig[(i - 1) * 8 + j] + orig[(i - 1) * 8 + j + 1] + orig[(i - 1) * 8 + j - 1] + orig[(i - 1) * 8 + j + 8] + orig[(i - 1) * 8 + j - 8]) / 10) + filter[4];
      sol[i * 8 + j] = result;
=======
  for (i = 8; i < 8184 - 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8192 - 8; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) >> 2)][j + ((k - 4) & 4)];
      }
      sol[i][j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}