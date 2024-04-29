Code: #pragma ACCEL kernel

void stencil(int orig[BDIM][BDIM],int sol[BDIM][BDIM],int filter[FILTER_BDIM][FILTER_BDIM])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < BDIM - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < BDIM - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < FILTER_BDIM; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int l = 0; l < FILTER_BDIM; l++) {
          sol[i][j] += filter[k][l] * orig[i + (-1 + k)][j + (-1 + l)];
        }
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:23: error: ‘BDIM’ undeclared here (not in a function)
    3 | void stencil(int orig[BDIM][BDIM],int sol[BDIM][BDIM],int filter[FILTER_BDIM][FILTER_BDIM])
      |                       ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:66: error: ‘FILTER_BDIM’ undeclared here (not in a function)
    3 | void stencil(int orig[BDIM][BDIM],int sol[BDIM][BDIM],int filter[FILTER_BDIM][FILTER_BDIM])
      |                                                                  ^~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: error: ‘BDIM’ undeclared (first use in this function)
   15 |   for (i = 1; i < BDIM - 1; i++) {
      |                   ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:19: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:23: error: ‘FILTER_BDIM’ undeclared (first use in this function)
   26 |       for (k = 0; k < FILTER_BDIM; k++) {
      |                       ^~~~~~~~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[BDIM_P][BDIM_P],int sol[BDIM_P][BDIM_P],int filter[FILTER_BDIM_P][FILTER_BDIM_P])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}