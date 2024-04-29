#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t_row;
  int t_col;
  int t_k;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        t_row = i + ((k / 3) - 1);
        t_col = j + ((k % 3) - 1);
        t_k = k;
        orig_row = 8192 + t_row;
        orig_col = 8192 + t_col;
        if (t_row < 0) {
          orig_row = 0;
        }
        if (t_col < 0) {
          orig_col = 0;
        }
        if (t_row >= 8) {
          orig_row = 8192 + 8;
        }
        if (t_col >= 8) {
          orig_col = 8192 + 8;
        }
        sol_row = i - 4 + ((k / 3) - 1);
        sol_col = j - 4 + ((k % 3) - 1);
        if (sol_row < 0) {
          sol_row = -1;
        }
        if (sol_col < 0) {
          sol_col = -1;
        }
        if (sol_row >= 8) {
          sol_row = 8;
        }
        if (sol_col >= 8) {
          sol_col = 8;
        }
        tmp += orig[orig_row * 8192 + orig_col] * filter[t_k];
      }
      sol[sol_row * 8192 + sol_col] = tmp;
    }
  }
}