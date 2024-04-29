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
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    middle:
    for (j = 0; j < 8192; j++) {
      inner:
      for (k = 0; k < 9; k++) {
<<<<<<< HEAD
        result += orig[i * 8192 + j] * filter[k];
=======
        result += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 8192 + j] = result;
      result = 0;
    }
  }
}