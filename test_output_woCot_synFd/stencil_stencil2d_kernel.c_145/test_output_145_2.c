Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        i_col = i - 4 + k_col[k];
        j_col = j - 4 + k_row[k];
        t += filter[k] * orig[i_col*64 + j_col];
      }
      sol[i*64 + j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:30: error: subscripted value is neither array nor pointer nor vector
   31 |         i_col = i - 4 + k_col[k];
      |                              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:25: error: ‘k_row’ undeclared (first use in this function)
   32 |         j_col = j - 4 + k_row[k];
      |                         ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:25: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        i_col = i - 4 + k_col[k];
        j_col = j - 4 + k_row[k];
        t += filter[k] * orig[i_col*64 + j_col];
      }
      sol[i*64 + j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:30: error: subscripted value is neither array nor pointer nor vector