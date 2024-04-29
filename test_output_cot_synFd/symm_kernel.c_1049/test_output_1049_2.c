Code: ### ACCEL kernel

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = alpha * temp1 + beta * C[i][j];
      C[i][j] = temp2;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘ACCEL’
    1 | ### ACCEL kernel
      |     ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:17: error: expected ‘;’ before ‘void’
    1 | ### ACCEL kernel
      |                 ^
      |                 ;
......
    5 | void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
      | ~~~~             

Please check the code and try again.
Code: ### Function Body
 c
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = alpha * temp1 + beta * C[i][j];
      C[i][j] = temp2;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Body
      | ^~
/root/autodl-