Code: #pragma ACCEL kernel

void stencil(int orig[N][M],int sol[N][M],int filter[WIDTH][WIDTH])
{
  int i;
  int j;
  int fl;
  int ft;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 1; i < N - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 1; j < M - 1; j++) {
      fl = filter[0][0] * orig[i][j];
      ft = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_filter:
      for (ft = 1; ft < WIDTH; ft++) {
        fl += filter[0][ft] * orig[i][j + ft];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_filter_t:
      for (ft = 1; ft < WIDTH; ft++) {
        fl += filter[ft][0] * orig[i + ft][j];
      }
      sol[i][j] = fl;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:23: error: ‘N’ undeclared here (not in a function)
    3 | void stencil(int orig[N][M],int sol[N][M],int filter[WIDTH][WIDTH])
      |                       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:26: error: ‘M’ undeclared here (not in a function)
    3 | void stencil(int orig[N][M],int sol[N][M],int filter[WIDTH][WIDTH])
      |                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:54: error: ‘WIDTH’ undeclared here (not in a function)
    3 | void stencil(int orig[N][M],int sol[N][M],int filter[WIDTH][WIDTH])
      |                                                      ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:19: error: ‘N’ undeclared (first use in this function)
   16 |   for (i = 1; i < N - 1; i++) {
      |                   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:19: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:24:21: error: ‘M’ undeclared (first use in this function)
   24 |     for (j = 1; j < M - 1; j++) {
      |                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:25: error: ‘WIDTH’ undeclared (first use in this function)
   30 |       for (ft = 1; ft < WIDTH; ft++) {
      |                         ^~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[N][M],int sol[N][M],int filter[WIDTH][WIDTH])
{
  int i;
  int j;
  int fl;
  int ft;