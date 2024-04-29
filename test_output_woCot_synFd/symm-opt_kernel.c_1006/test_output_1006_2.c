Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
        for (jj = 0; jj < 60; jj++) {
          double temp1 = A[i][jj] * B[jj][j];
          temp2 += temp1;
        }
	C[i][j] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: error: stray ‘##’ in program
    3 | ### Parameters:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘#’ in program
    3 | ### Parameters:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    3 | ### Parameters:
      |               ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:1: error: stray ‘##’ in program
   10 | ### Types:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘#’ in program
   10 | ### Types:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:1: error: stray ‘##’ in program
   20 | ### Packages:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:3: error: stray ‘#’ in program
   20 | ### Packages:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:87:14: error: ‘jj’ undeclared (first use in this function); did you mean ‘j’?
   87 |         for (jj = 0; jj < 60; jj++) {
      |              ^~
      |              j
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:87:14: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL