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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
    for (row_up = row - 1; row_up >= 1; row_up--) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_left:
      for (col_left = col - 1; col_left >= 1; col_left--) {
        t += orig[row_up * 8192 + col_left] * filter[0];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_middle:
      for (col = 1; col < 8192 - 1; col++) {
        t += orig[row_up * 8192 + col] * filter[1];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_right:
      for (col_right = col_left + 1; col_right < 8192; col_right++) {
        t += orig[row_up * 8192 + col_right] * filter[2];
      }
      sol[row * 8192 + col] = t;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_down:
    for (row_down = row_up + 1; row_down < 8191; row_down++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_left:
      for (col_left = col_left; col_left < 8192; col_left++) {
        t += orig[row_down * 8192 + col_left] * filter[0];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_middle:
      for (col = col; col < 8192 - 1; col++) {
        t += orig[row_down * 8192 + col] * filter[1];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_right:
      for (col_right = col_right; col_right < 8191; col_right++) {
        t += orig[row_down * 8192 + col_right] * filter[2];
      }
      sol[row * 8192 + col] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:56:7: error: duplicate label ‘loop_col_left’
   56 |       loop_col_left:
      |       ^~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:29:7: note: previous definition of ‘loop_col_left’ was here
   29 |       loop_col_left:
      |       ^~~~~~~~~~~~~