 

#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,doubletmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
     tmp[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (k = 0; k < 70; k++) 
     tmp[i][k] = alpha * A[i][k] * B[k][j];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      D[i][j] *= beta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
      D[i][j] += 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      D[i][j] += 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (k = 0; k < 50; k++) 
      C[i][k] *= 2.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 50; j++) 
      B[i][j] *= 2.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 70; j++) 
      A[i][j] *= 2.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 80; j++) 
      D[i][j