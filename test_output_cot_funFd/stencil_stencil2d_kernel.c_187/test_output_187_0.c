**Function Body:**
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
    for (row_up = row - 1; row_up >= 1; row_up--) {
      t = row_up * 32 + 1;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      loop_col_up:
      for (col_up = 31; col_up >= 1; col_up--) {
        i = t + col_up;
        sol[i] = ((0 + 
                   filter[0]) * orig[i] + (0 + 
                                           filter[1]) * orig[i + 1] + (0 + 
                                                                       filter[2]) * orig[i + 32] + (0 + 
                                                                                                    filter[3]) * orig[i + 33] + (0 + 
                                                                                                                                 filter[4]) * orig[i + 32 - 1] + (0 + 
                                                                                                                                                                         filter[5]) * orig[i + 33 - 1] + (0 + 
                                                                                                                                                                                                 filter[6]) * orig[i + 1 - 32] + (0 + 
                                                                                                                                                                                                                         filter[7]) * orig[i + 1 - 33] + (0 + 
                                                                                                                                                                                                                                                 filter[8]) * orig[i - 1]) / (0 + 
                                                                                                                                                                                                                                                             filter[0] + filter[1] + filter[2] + filter[3] + filter[4] + filter[5] + filter[6] + filter[7] + filter[8]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 32; col++) {
      t = row * 32 + col;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = t + k - 4;
        sol[i] = ((filter[k] + 
                   sol[i]) * orig[i]) / (filter[k] + 1);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_down:
    for (row_down = row + 1; row_down < 33; row_down++) {
      t = row_down * 32 + 1;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      loop_col_down:
      for (col_down = 31; col_down >= 1; col_down--) {
        i = t + col_down;
        sol[i] = ((0 + 
                   filter[0]) * sol[i] + (0 + 
                                           filter[1]) * sol[i - 1] + (0 + 
                                                                       filter[2]) * sol[i - 32] + (0 + 
                                                                                                    filter[3]) * sol[i - 33] + (0 + 
                                                                                                                                 filter[4]) * sol[i - 32 + 1] + (0 + 
                                                                                                                                                                         filter[5]) * sol[i - 33 + 1] + (0 + 
                                                                                                                                                                                                 filter[6]) * sol[i + 1 - 32] + (0 + 
                                                                                                                                                                                                                         filter[7]) * sol[i + 1 - 33] + (0 + 
                                                                                                                                                                                                                                                 filter[8]) * sol[i + 1]) / (0 + 
                                                                                                                                                                                                                                                             filter[0] + filter[1] + filter[2] + filter[3] + filter[4] + filter[5] + filter[6] + filter[7] + filter[8]);
      }
    }
  }
}