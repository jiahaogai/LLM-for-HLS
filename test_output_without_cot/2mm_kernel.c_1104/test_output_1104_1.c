#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][50],double A[40][80],double B[80][50],double D[40][50])
  for(i = 0; i < 40; i++)
  for(j = 0; j < 50; j++)
    C[i][j] *= beta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for(i = 0; i < 40; i++)
  for(j = 0; j < 50; j++)
    for(k = 0; k < 80; ++k)
      C[i][j] += alpha * A[i][k] * B[k][j];
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for(i = 0; i < 40; i++)
  for(j = 0; j < 50; j++)
    for(k = 0; k < 80; ++k)
      D[i][j] += A[i][k] * D[k][j];
}