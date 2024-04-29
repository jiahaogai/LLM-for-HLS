Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loop_x:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
  for (i = 0; i <= 7; i++) {
     row = 8 * i;
     row_up = 8 * (i - 1);
     row_down = 8 * (i + 1);
     loop_y:
/* Standardize from: for(j = 0; j < 8; j++) {...} */
    for (j = 0; j <= 7; j++) {
      col = 8 * j;
      col_up = 8 * (j - 1);
      col_down = 8 * (j + 1);
      tid = row + col;
      flit = 0;
      loop_f:
      for (jj = 0; jj < 9; jj++) {
        if (((8 & ((~0 << 3) + 1)) >> 3) & (1 << jj)) {
          if (((8 & ((~0 << 3) + 1)) >> 3) & (1 << jj)) {
            if (jj == 4) {
              flit = orig[tid];
            }
            
#pragma ACCEL PIPELINE auto{flatten}
            
#pragma ACCEL TILE FACTOR=auto{1}
            if (((8 & ((~0 << 1) + 1)) >> 1) & (1 << jj)) {
              sol[tid] = flit;
            }
          }
        }
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:12: error: ‘jj’ undeclared (first use in this function); did you mean ‘j’?
   34 |       for (jj = 0; jj < 9; jj++) {
      |            ^~
      |            j
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:12: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loop_x:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
  for (i = 0; i <= 7; i++) {
     row = 8 * i;
     row_up = 8 * (i - 1);
     row_down = 8 * (i + 1);
     loop_y:
/* Standardize from: for(j = 0; j < 8; j++) {...} */
    for (j = 0; j <= 7; j++) {
      col = 8 * j;
      col_up = 8 * (j - 1);
      col_down = 8 * (j + 1);
      tid = row +