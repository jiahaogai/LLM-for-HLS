#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
<<<<<<< HEAD
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k_row = -4; k_row < 5; k_row++) {
          k = k_row + 4 + ((k_col + 4) * 64);
          sum += filter[k] * orig[k];
        }
=======
      for (k = 0; k < 9; k++) {
        k_col = ((j + 4) - (8 + ((k * 2) - 1)));
        k_col = (k_col < 0 ? 0 : k_col);
        k_col = (k_col > 63 ? 63 : k_col);
        k_row = ((i + 4) - (8 + ((k * 2) - 1)));
        k_row = (k_row < 0 ? 0 : k_row);
        k_row = (k_row > 63 ? 63 : k_row);
        sum += filter[k] * orig[k_row * 64 + k_col];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 64 + j] = sum;
    }
  }
}