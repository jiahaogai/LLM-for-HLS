#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int sum;
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 0; i < 8192; i++) {
    t = orig[i] * filter[0];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (i * 256 + j) * 256 + k;
        val += filter[(((k + 4) < 0 ? (-1 * (k + 4)) : (k + 4))) - 4] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
=======
    for (j = 1; j < 9; j++) {
      t += orig[i + j] * filter[j];
    }
    sum = t;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 9; j++) {
      t = orig[i] * filter[j];
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (k = 1; k < 9; k++) {
        t += orig[i + k] * filter[k * 9 + j];
      }
      sol[i + j] = sum - t;
    }
    sol[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}