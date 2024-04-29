Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int range;
  int center;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      min_i = (8192 + i - 1) % 8192;
      max_i = (i + 1) % 8192;
      min_j = (8192 + j - 1) % 8192;
      max_j = (j + 1) % 8192;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      range = 4;
      center = 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[range * min_i + center + k - 4];
      }
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
      sol[max_i * 8192 + max_j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:42:12: error: ‘k’ undeclared (first use in this function)
   42 |       for (k = 0; k < 9; k++) {
      |            ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:42:12: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_row;
  int max_row;
  int min_col;
  int max_col;
  int range;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loop_row_up:
/* Standardize from: for(row = 1; row < 64 + 1 - 4; row++) {...} */
  for (row = 1 + 4 - 1; row < 64 + 1 - 1 + 4 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col_up:
/* Standardize from: for(col = 1; col < 64 + 1 - 4; col++) {...} */
    for (col = 1 + 4 - 1; col < 64 + 1 -