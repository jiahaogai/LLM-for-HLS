Code: #pragma ACCEL kernel

void kernel_symm(int ni,int nj,double alpha,double beta,double C[200][220],double A[200][240],double B[240][220])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{70}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 240; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 220; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{2}
        for (l = 0; l < 240; l++) {
          temp1[l] = A[i][l] * B[l][j];
        }
        for (l = 0; l < 240; l++) {
          temp2 += temp1[l];
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:40:14: error: ‘l’ undeclared (first use in this function)
   40 |         for (l = 0; l < 240; l++) {
      |              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:40:14: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:41:11: error: ‘temp1’ undeclared (first use in this function); did you mean ‘temp2’?
   41 |           temp1[l] = A[i][l] * B[l][j];
      |           ^~~~~
      |           temp2

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(int ni,int nj,double alpha,double beta,double C[200][220],double A[200][240],double B[240][220])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FA