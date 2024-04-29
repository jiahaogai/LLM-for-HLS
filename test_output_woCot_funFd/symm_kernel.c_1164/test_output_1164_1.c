Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{1}
        for (jj = 0; jj < 60; jj++) {
          temp1 = A[i][jj] * B[jj][j];
          temp2 += temp1;
        }
	C[i][j] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: error: ‘jj’ undeclared (first use in this function); did you mean ‘j’?
   34 |         for (jj = 0; jj < 60; jj++) {
      |              ^~
      |              j
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:11: error: ‘temp1’ undeclared (first use in this function); did you mean ‘temp2’?
   35 |           temp1 = A[i][jj] * B[jj][j];
      |           ^~~~~
      |           temp2
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:24: error: ‘B’ undeclared (first use in this function); did you mean ‘A’?
   35 |           temp1 = A[i][jj] * B[jj][j];
      |                        ^~
      |                        A
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:33: error: ‘j’ undeclared (first use in this function); did you mean ‘jj’?
   35 |           temp1 = A[i][jj] * B[jj][j];
      |                                 ^
      |                                 jj
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:36:28: error: ‘temp2’ undeclared (first use in this function); did you mean ‘temp1’?
   36 |           C[i][j] += alpha * temp2;
      |                            ^~~~~
      |                            temp1
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:36:28: note: each undeclared identifier is reported only once for each function it appears in