#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double tmp;
  double mult;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        mult = A[i][k] * B[k][j];
        tmp += mult;
      }
      C[i][j] = tmp;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] += alpha * tmp;
    }
    
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      temp2 += C[i][j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * temp2;
    }
  }
}