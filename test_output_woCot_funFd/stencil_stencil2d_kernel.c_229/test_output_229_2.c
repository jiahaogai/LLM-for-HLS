#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
=======
  int k;
  int k_col;
  int i_col;
  int j_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
  for (j = 8; j < 992; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 8; i < 992; i++) {
      t = 0;
      row_up = (8 + 8 - 1 >= 8) ? 8 : 8 + 8 - 1;
      row_down = (8 + 8 + 2 <= 992 - 1) ? 8 + 8 + 2 : 992 - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopcol_up:
      for (col_up = (8 + 8 - 1 >= 8) ? 8 : 8 + 8 - 1; col_up <= (8 + 8 + 2 <= 992 - 1) ? 8 + 8 + 2 : 992 - 1; col_up++) {
        t += filter[0] * orig[row_up * 992 + col_up];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopcol_down:
      for (col_down = (8 + 8 + 2 <= 992 - 1) ? 8 + 8 + 2 : 992 - 1; col_down >= (8 + 8 - 1 >= 8) ? 8 : 8 + 8 - 1; col_down--) {
        t += filter[2] * orig[row_down * 992 + col_down];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopcol:
      for (col = 1; col <= 8; col++) {
        t += filter[col] * orig[(8 + 8) * 992 + col + ((j - 8) * 992) + i];
      }
      sol[j * 992 + i] = t;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = (i - 1 + 256) % 256;
      j_col = (j - 1 + 256) % 256;
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = (k - 1 + 256) % 256;
        sum += filter[k] * orig[i_col * 256 + k_col];
      }
      sol[i * 256 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}