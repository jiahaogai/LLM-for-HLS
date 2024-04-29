Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  int jj;
  int kk;
  double mult_tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      mult_tmp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 60; k++) {
        jj = (80 + 1) * (k + 1) - 1;
        kk = (80 + 1) * (i + 1) - 1;
        mult_tmp += A[kk][jj] * A[kk][jj];
      }
      C[i][j] *= beta;
      C[i][j] += alpha * mult_tmp;
    }
  }
}