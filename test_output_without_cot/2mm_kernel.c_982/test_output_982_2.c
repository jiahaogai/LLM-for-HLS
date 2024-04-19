#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
  for(int i = 0; i < 40; i++)
  for(int j = 0; j < 50; j++)
    tmp[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  for(int i = 0; i < 40; i++)
  for(int j = 0; j < 80; j++)
    D[i][j] *= beta;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  for(int i = 0; i < 40; i++)
  for(int j = 0; j < 50; j++)
  for(int k = 0; k < 70; k++)
    tmp[i][j] += alpha * A[i][k] * B[k][j];
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  for(int i = 0; i < 40; i++)
  for(int j = 0; j < 80; j++)
    D[i][j] += tmp[i][k] * C[k][j];
}