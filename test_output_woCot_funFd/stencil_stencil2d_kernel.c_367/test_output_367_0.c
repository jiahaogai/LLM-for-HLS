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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  loopj:
  for (j = 8; j < 8184; j++) {
=======
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    loopk_col:
    for (k_col = 1; k_col < 9; k_col++) {
      sum = 0.0;
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 9 + k_col;
        sum += filter[k] * orig[j - 4 + k_row];
      }
      sol[j - 8 + k_col] = sum;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i - 4 + j;
      if (k_col < 0 || k_col > 8191) {
        k_col = 0;
      }
      inner_parallel:
      for (k = 0; k < 9; k++) {
        k_row = k_col - 4 + k;
        if (k_row < 0 || k_row > 8191) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row];
      }
    }
    sol[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}