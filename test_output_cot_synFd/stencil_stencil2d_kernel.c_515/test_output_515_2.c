Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 1;
      sol[row + col] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        flit = filter[k] * orig[row + col + flit_in_col[k]];
        sol[row + col] += flit;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:45: error: ‘flit_in_col’ undeclared (first use in this function)
   31 |         flit = filter[k] * orig[row + col + flit_in_col[k]];
      |                                             ^~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:45: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 1;
      sol[row + col] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        flit = filter[k] * orig[row + col + flit_in_col[k]];
        sol[row + col] += flit;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:45: error: ‘flit_in_col’ undeclared (first