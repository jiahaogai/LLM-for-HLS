#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      middle:
=======
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 8) * k) + i;
        i_col = ((8192 + 8) * k) + j;
        sum += filter[k] * orig[k_col] * orig[i_col];
      }
<<<<<<< HEAD
      sol[i_col] = sum;
=======
      sol[j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}