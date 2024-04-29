#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
  int t;
=======
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
<<<<<<< HEAD
    t = orig[i] * filter[0];
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
    inner1:
    for (j = 1; j < 9; j++) {
      t += orig[i + j] * filter[j];
    }
    sol[i] = t;
=======
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = orig[i * 8 + j * 1 + k] * filter[k];
        sol[i * 8 + j * 1 + k] = result;
      }
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}