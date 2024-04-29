#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
<<<<<<< HEAD
  int i_col;
=======
  int k_row;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 0; i < 64; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + 4;
        i_col = i + k_col;
        if ((((i_col >= 0) && (i_col < 8192))) && (((j >= 0) && (j < 8192)))) {
          sum += filter[k + 4] * orig[i_col] * orig[j];
        }
      }
      sol[i * 8192 + j] = sum;
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k % 8));
        k_row = ((8 * j) + (k / 8));
        sum += filter[k] * orig[k_row * 64 + k_col];
      }
      sol[i * 64 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}