Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[400][400],double A[400][300])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNI
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 300; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 300; j++) {
        C[i][j] += alpha * A[i][k] * A[k][j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘`’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:36: error: stray ‘`’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:37: error: expected identifier or ‘(’ before ‘:’ token
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:36: error: stray ‘`’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |                                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/