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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      int middle_reg_0 = filter[0];
      int middle_reg_1 = filter[1];
      int middle_reg_2 = filter[2];
      int middle_reg_3 = filter[3];
      int middle_reg_4 = filter[4];
      int middle_reg_5 = filter[5];
      int middle_reg_6 = filter[6];
      int middle_reg_7 = filter[7];
      int middle_reg_8 = filter[8];
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (row = i - 8; row <= i + 8; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = j - 8; col <= j + 8; col++) {
          t += orig[row * 8192 + col] * middle_reg_0;
          middle_reg_0 = middle_reg_1;
          middle_reg_1 = middle_reg_2;
          middle_reg_2 = middle_reg_3;
          middle_reg_3 = middle_reg_4;
          middle_reg_4 = middle_reg_5;
          middle_reg_5 = middle_reg_6;
          middle_reg_6 = middle_reg_7;
          middle_reg_7 = middle_reg_8;
          middle_reg_8 = orig[row * 8192 + col + 1];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}