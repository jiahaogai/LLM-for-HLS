#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t_row;
  int t_col;
  int t_row_start;
  int t_row_end;
  int t_col_start;
  int t_col_end;
  int t_i;
  int t_j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        t_row_start = i - 4 + k / 8;
        t_row_end = i - 4 + 1 + k / 8;
        t_col_start = j - 4 + k % 8;
        t_col_end = j - 4 + 1 + k % 8;
        row:
        for (t_row = t_row_start; t_row <= t_row_end; t_row++) {
          
#pragma ACCEL PARALLEL reduction=tmp collapse=row FACTOR=auto{1}
          col:
          for (t_col = t_col_start; t_col <= t_col_end; t_col++) {
            if (t_row < 0 || t_row > 8191 || t_col < 0 || t_col > 8191) {
              tmp += 0;
            }
             else {
              tmp += orig[t_row * 8192 + t_col] * filter[k];
            }
          }
        }
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}