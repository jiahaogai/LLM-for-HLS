#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      inner:
      for (k = 0; k < 8; k++) {
        result += filter[k] * orig[i + k - 4];
      }
      sol[i + j - 4] = result;
=======
    for (j = 0; j < 8192; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}