#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  for (i = 0; i < 8192; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 8 + j + k - 4];
      }
      sol[i * 8 + j] = result;
=======
    for (j = 0; j < 8192; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4];
      }
      sol[j] = result;
      result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}