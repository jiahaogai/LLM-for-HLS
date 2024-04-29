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
  for (i = 0; i < 8; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((j + 4) - (k % 5)) < 0 ? (j + 4) - ((k % 5) - 5) : (j + 4) - (k % 5);
        k_col = k_col >= 8192 ? 8191 : k_col;
        k_row = i - (k - (k / 5) * 5);
        k_row = k_row >= 8192 ? 8191 : k_row;
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
=======
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k % 8));
        k_row = ((8 * j) + (k / 8));
        sum += filter[k] * orig[k_row * 8 + k_col];
      }
      sol[(8 * i) + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}