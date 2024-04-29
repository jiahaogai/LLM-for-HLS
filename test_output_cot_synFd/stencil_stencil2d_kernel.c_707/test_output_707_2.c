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
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 32; i++) {
      row_up = 0;
      
#pragma ACCEL CONDITIONAL=auto{i>1}
      row_up = (i - 1) * 32 + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_col:
      for (k_col = 0; k_col < 9; k_col++) {
        row = row_up + k_col;
        col_up = 0;
        
#pragma ACCEL CONDITIONAL=auto{k_col>1}
        col_up = (k_col - 1) * 32;
        col_down = 0;
        
#pragma ACCEL CONDITIONAL=auto{k_col<8}
        col_down = (8 - k_col) * 32;
#pragma ACCEL PARALLEL FACTOR=auto{32}
        loopk:
        for (k = col_up; k < col_down; k++) {
          val = orig[row * 32 + k];
          sol[row * 32 + k] = ((val + filter[k_col]) +
                               ((val + filter[k_col + 9]) >> 1) +
                               ((val + filter[k_col + 18]) >> 2) +
                               ((val + filter[k_col + 27]) >> 3)) >> 3;
        }
      }
    }
  }
}