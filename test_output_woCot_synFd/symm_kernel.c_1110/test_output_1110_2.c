Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        int _in_j = 0;
        int _in_k = 0;
        for (_in_j = 0; _in_j < 80; _in_j++) {
          int _A_idx = _in_k * 80 + _in_j;
          double _A_val = A[_A_idx];
          int _B_idx = _in_k * 60 + _in_j;
          double _B_val = B[_B_idx];
          {
            temp2 += _A_val * _B_val;
          }
        }
        int _C_idx = i * 80 + j;
        C[_C_idx] += alpha * temp2;
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:38:27: error: incompatible types when initializing type ‘double’ using type ‘double *’
   38 |           double _A_val = A[_A_idx];
      |                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:40:27: error: incompatible types when initializing type ‘double’ using type ‘double *’
   40 |           double _B_val = B[_B_idx];
      |                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:46:19: error: assignment to expression with array type
   46 |         C[_C_idx] += alpha * temp2;
      |                   ^~

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma