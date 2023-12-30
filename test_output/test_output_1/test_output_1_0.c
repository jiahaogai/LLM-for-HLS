

 #pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,doubletmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
{
  int i;
  int j;
  int k;
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
     tmp[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) 
    for (k = 0; k < 70; k++) 
     tmp[i][k] = 0.0;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
      A[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) 
    for (k = 0; k < 50; k++) 
      B[i][k] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      C[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      D[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      D[i][j] = 0.0;
  
#pragma ACCEL PARALLEL reduction = variable FACTOR=auto{1}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
      D[i][j] = 0.0;
  
#pragma ACCEL PARALLEL reduction = variable FACTOR=auto{8}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
      A[i][j] = (double )0;
  
#pragma ACCEL PARAL