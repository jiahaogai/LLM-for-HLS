Code: #pragma ACCEL kernel

void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[SIZE][SIZE])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < SIZE - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < SIZE - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < SIZE; k++) {
        sol[i][j] += filter[k][0] * orig[i - 1 + k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:23: error: ‘SIZE’ undeclared here (not in a function)
    3 | void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[SIZE][SIZE])
      |                       ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: error: ‘SIZE’ undeclared (first use in this function)
   15 |   for (i = 1; i < SIZE - 1; i++) {
      |                   ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[SIZE][SIZE])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < SIZE - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < SIZE - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < SIZE; k++) {
        sol[i][j] += filter[k][0] * orig[i - 1 + k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:23: error: ‘SIZE’ undeclared here (not in a function)
    3 | void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[SIZE][SIZE])
      |                       ^~~~
/root/