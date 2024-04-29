#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 9; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[j] * orig[i + k - 4];
      }
      sol[i + j - 4] = result;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 8 + j] * orig[i * 8 + j];
      }
      sol[i * 8 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      result = 0;
    }
  }
}