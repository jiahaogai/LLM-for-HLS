Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_dgemm() {
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form D := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
//D is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      for (j = 0; j < 80; j++) {
        double sum = 0.0;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (l = 0; l < 60; l++) {
          sum += A[i][l] * B[l][j];
        }
        D[i][j] += alpha * sum;
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_dgemm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:48:14: error: ‘l’ undeclared (first use in this function)
   48 |         for (l = 0; l < 60; l++) {
      |              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:48:14: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_dgemm() {
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form D := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
//D is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma