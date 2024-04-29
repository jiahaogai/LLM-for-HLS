Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spack_c:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    spack_b:
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      spack_a:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mult = alpha * A[i][k] * B[k][k_col];
        temp_x += mult;
      }
      C[i][j] += temp_x;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spack_d:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    spack_a:
    for (j = 0; j < 80; j++) {
      temp_y = 0.0;
      spack_b:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mult = alpha * B[k][k_col] * C[k][i];
        temp_y += mult;
      }
      C[i][j] = temp_y + beta * C[i][j];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:7: error: ‘temp_x’ undeclared (first use in this function)
   26 |       temp_x = 0.0;
      |       ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:7: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:50:5: error: duplicate label ‘spack_a’
   50 |     spack_a:
      |     ^~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:7: note: previous definition of ‘spack_a’ was here
   27 |       spack_a:
      |       ^~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:52:7: error: ‘temp_y’ undeclared (first use in this function)
   52 |       temp_y = 0.0;
      |       ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:53:7: error: duplicate label ‘spack_b’
   53 |       spack_b:
      |       ^~~~~~~
/root/autodl-