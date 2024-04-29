Code: ### Function Definition:
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{30}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        int s1 = i * 60 + k;
        int s2 = k * 80 + j;
        for (int _in_j_0 = 0; _in_j_0 < 60; _in_j_0++) {
          double _in_A = A[s1 + _in_j_0];
          double _in_B = B[_in_j_0 * 80 + j];
          temp1 += _in_A * _in_B;
        }
        C[i][j] += alpha * temp1;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Definition:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Definition:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Function’; did you mean ‘union’?
    1 | ### Function Definition:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Function Definition:
      |                  ^

Please check the code and try again.
Code: ### Function Body:
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (k = 0; k < 60; k++) {
      
#pragma ACC