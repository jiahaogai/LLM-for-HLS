Below, we provide the actual HLS code snippet for reference.
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
  int col;
  int col_up;
  int col_down;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      row_up = (i == 0 ? 0 : i - 1);
      row_down = (i == 8191 ? 8191 : i + 1);
      col_up = (j == 0 ? 0 : j - 1);
      col_down = (j == 8191 ? 8191 : j + 1);
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k + j - 4;
        row = k_col < 0 ? 0 : k_col > 8191 ? 8191 : k_col;
        tmp += filter[k] * orig[row];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}