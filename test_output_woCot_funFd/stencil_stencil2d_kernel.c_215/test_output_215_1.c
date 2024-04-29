#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int row_up;
  int row_down;
  int r;
  int orig_row;
  int sol_row;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row_up = (i - 1 + 8) % 8;
      row_down = (i + 1) % 8;
      orig_row = i * 8 + j;
      sol_row = orig_row;
/*#pragma ACCEL PIPELINE auto{off}*/
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = k * 8 + j;
        r = filter[k] * orig[k_col];
        sol[sol_row] = r;
        sol_row = row_up * 8 + k_col;
        sol[sol_row] = r;
        sol_row = row_down * 8 + k_col;
        sol[sol_row] = r;
      }
    }
  }
}