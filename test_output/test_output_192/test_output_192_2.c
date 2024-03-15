

 #pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int alpha,int beta,int tmp[60][80],double A[60][60],double B[60][80],double C[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      tmp[i][j] = A[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2_0}
      for (k = 0; k < 60; k++) {
        sum += alpha * tmp[i][k] * B[k][j];
      }
      C[i][j] = beta * C[i][j] + sum;
    }
  }
//#pragma endscop
}
