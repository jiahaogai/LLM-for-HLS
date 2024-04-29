Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8192; j += 8) {
      t = 0;
      int middle_reg_0 = 0;
      int middle_reg_1 = 0;
      int middle_reg_2 = 0;
      int middle_reg_3 = 0;
      int middle_reg_4 = 0;
      int middle_reg_5 = 0;
      int middle_reg_6 = 0;
      int middle_reg_7 = 0;
      int middle_reg_8 = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -4; k <= 4; k++) {
        row_up = i - 4;
        row_down = i + 4;
        if (row_up < 0) {
          row_up = 0;
        }
        if (row_down >= 8192) {
          row_down = 8191;
        }
        col_left = j - 4;
        col_right = j + 4;
        if (col_left < 0) {
          col_left = 0;
        }
        if (col_right >= 8192) {
          col_right = 8191;
        }
        row = row_up + k;
        if (row < row_up) {
          row = row_up;
        }
        if (row > row_down) {
          row = row_down;
        }
        if (row < 0 || row > 8191) {
          _inva_row = -1;
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_mid:
        for (l = -4; l <= 4; l++) {
          col = col_left + l;
          if (col < col_left) {
            col = col_left;
          }
          if (col > col_right) {
            col = col_right;
          }
          if (col < 0 || col > 8191) {
            _inva_col = -1;
          }
          t += filter[k + 4] * orig[row * 8192 + col];
          middle_reg_0 += filter[k + 4] * orig[row * 8192 + col];
          middle_reg_1 += filter[k + 3] * orig[row * 8192 + col];
          middle_reg_2 += filter[k + 2] * orig[row * 8192 + col];
          middle_reg_3 += filter[k + 1] * orig[row * 8192 + col];
          middle_reg_4 += filter[k + 0] * orig[row * 8192 + col];
          middle_reg_5 += filter[k - 1] * orig[row * 8192 + col];
          middle_reg_6 += filter[