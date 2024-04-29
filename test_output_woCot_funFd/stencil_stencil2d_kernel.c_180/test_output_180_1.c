#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
<<<<<<< HEAD
      for (k = -4; k < 5; k++) {
        k_col = j + k;
        if (k_col < 0) {
          k_col += 8192;
        }
        else {
          if (k_col > 8191) {
            k_col -= 8192;
          }
        }
        k_row = i + k;
        if (k_row < 0) {
          k_row += 8192;
        }
        else {
          if (k_row > 8191) {
            k_row -= 8192;
          }
        }
        sum += filter[k + 4] * orig[k_row * 8192 + k_col];
=======
      for (k = 0; k < 9; k++) {
        k_col = ((8192 / 9) * k) + j;
        k_row = i + ((8192 / 9) * k);
        sum += filter[k] * orig[k_row * 8192 + k_col];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 8192 + j] = sum;
    }
  }
}