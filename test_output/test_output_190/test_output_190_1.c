

  int tsteps;
  int n;
  int b;
  double A[60][80];
  double B[80][90];
  double C[60][90]
      ;
  
#pragma ACCEL kernel

void kernel_gemm(int tsteps,int n,int m,int p,double alpha,double beta,double A[60][80],double B[80][90],double C[60][90])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 60; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 0; i < 80; i++) {
      C[t][i] *= beta;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 90; j++) {
      for (i = 0; i < 80; i++) {
        C[t][j] += alpha * A[t][i] * B[i][j];
      }
    }
  }
//#pragma endscop
}
