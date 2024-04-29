Code: #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      C[j][j] += alpha * A[j][k] * B[j][k];
    }
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      C[j][j] += beta * A[j][k] * B[k][j];
    }
  }
//#pragma endscop
}