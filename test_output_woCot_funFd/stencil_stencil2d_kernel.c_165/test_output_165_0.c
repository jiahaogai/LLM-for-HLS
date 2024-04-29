#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 0; i < 64; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
=======
    for (j = 0; j < 64; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      sum = 0.0;
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = i - 4 + k_col;
<<<<<<< HEAD
        if ((k_row >= 0) && (k_row < 8192)) {
          k = k_row * 8192 + j;
          sum += filter[k_col] * orig[k];
        }
      }
      sol[i * 8192 + j] = sum;
=======
        if ((k_row >= 0) && (k_row < 64)) {
          k = k_row * 64 + j;
          sum += filter[k_col] * orig[k];
        }
      }
      sol[i * 64 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}