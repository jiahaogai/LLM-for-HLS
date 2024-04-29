#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
    }
  }
}