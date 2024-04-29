Code: 
#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double tmp;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{2}
      for (k = 0; k < 60; ++k) {
        tmp += A[i][k] * B[k][j];
      }
      C[i][j] += tmp * alpha;
    }
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * C[j][i];
    }
  }
  
#pragma endscop
}