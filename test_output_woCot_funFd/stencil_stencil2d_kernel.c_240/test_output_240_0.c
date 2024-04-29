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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
<<<<<<< HEAD
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-1 + k) * 8190];
      }
      sol[i * 8190 + j] = result;
=======
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192 + j];
      }
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}