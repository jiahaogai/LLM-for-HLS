kernel_syrk
#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  int jj;
  int kk;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        jj = (((80 + 0) - 1) - j);
        kk = (((60 + 0) - 1) - k);
        tmp += alpha * A[i][k] * A[j][kk];
      }
      C[i][j] = beta * C[i][j] + tmp;
    }
  }
}