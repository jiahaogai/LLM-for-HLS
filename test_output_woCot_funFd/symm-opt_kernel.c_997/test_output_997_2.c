Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double tmp;
  double mul;
  double tmp1 = 0.0;
  double tmp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      tmp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{16}
      for (k = 0; k < 60; k++) {
        mul = A[i][k] * B[k][j];
        tmp1 += mul;
      }
      tmp = tmp1 * alpha;
      tmp2 += tmp;
      C[i][j] += tmp;
    }
    tmp = tmp2 * beta;
    C[i][tmp.index] += tmp;
    tmp2 = 0.0;
    tmp1 = 0.0;
  }
}