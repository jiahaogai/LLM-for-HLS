Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int fidx;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 64 + 1 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    loop_col:
    for (col = 1; col < 128 + 1 - 1; col++) {
      idx = (row - 1) * 128 + col - 1;
      row_up = row - 1;
      row_down = row + 1;
      col_up = col - 1;
      col_down = col + 1;
      if (row_up == 0) {
        row_up = 1;
      }
      if (col_up == 0) {
        col_up = 1;
      }
      if (row_down == 64 + 1 - 1) {
        row_down = 64;
      }
      if (col_down == 128 + 1 - 1) {
        col_down = 128;
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_up * 128 + col_up - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_up * 128 + col_down - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_down * 128 + col_up - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_down * 128 + col_down - 1];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:53:7: error: duplicate label ‘loop_fidx’
   53 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:49:7: note: previous definition of ‘loop_fidx’ was here
   49 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:57:7: error: duplicate label ‘loop_fidx’
   57 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:49:7: note: previous definition of ‘loop_fidx’ was here
   49 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:61:7: error: duplicate label ‘loop_fidx’
   61 |