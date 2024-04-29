Code: #pragma ACCEL kernel

void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[FILTER_SIZE][FILTER_SIZE])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < SIZE - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < SIZE - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1]) + (filter[2][0] * orig[i + 1][j - 1]) + (filter[2][1] * orig[i + 1][j]) + (filter[2][2] * orig[i + 1][j + 1])) / 4;
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:23: error: ‘SIZE’ undeclared here (not in a function)
    3 | void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[FILTER_SIZE][FILTER_SIZE])
      |                       ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:66: error: ‘FILTER_SIZE’ undeclared here (not in a function)
    3 | void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[FILTER_SIZE][FILTER_SIZE])
      |                                                                  ^~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: error: ‘SIZE’ undeclared (first use in this function)
   15 |   for (i = 1; i < SIZE - 1; i++) {
      |                   ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[DIM][DIM],int sol[DIM][DIM],int filter[FILTER_DIM][FILTER_DIM])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < DIM - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < DIM - 1; j++) {
      sol[i][j]