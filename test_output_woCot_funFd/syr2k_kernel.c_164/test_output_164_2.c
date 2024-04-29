Code: ### Unpacking (C):
0. @C(ALPHA,double) 
1. @C(BETA,double) 
2. @C(C,double[80][80]) 
3. @C(A,double[80][60]) 
4. @C(B,double[80][60]) 

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Unpacking (C):
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Unpacking (C):
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: warning: return type defaults to ‘int’ [-Wimplicit-int]
    1 | ### Unpacking (C):
      |     ^~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘Unpacking’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:16: error: expected declaration specifiers before ‘:’ token
    1 | ### Unpacking (C):
      |                ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘@’ in program
    2 | 0. @C(ALPHA,double)
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘@’ in program
    3 | 1. @C(BETA,double)
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘@’ in program
    4 | 2. @C(C,double[80][80])
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:4: error: stray ‘@’ in program
    5 | 3. @C(A,double[80][60