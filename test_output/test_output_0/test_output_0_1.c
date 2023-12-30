 #pragma ACCEL kernel

void kernel_2mm_2D_D(int ni,int nj,int nk,int nl,double alpha,double beta,doubletmp[40][40],double A[40][40],double B[40][40],double C[40][40],doubleD[40][40])
{
  int i;
  int j;
  int k;
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
     tmp[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (k = 0; k < 40; k++) 
     tmp[i][k] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 0; j < 40; j++) 
    for (k = 0; k < 40; k++) 
     tmp[j][k] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
     D[i][j] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
     D[i][j] = 0.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
      B[i][j] = alpha * (tmp[i][j] + A[i][k] * B[k][j]);
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
      C[i][j] = alpha * (tmp[i][j] + A[i][k] * C[k][j]);
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{40}
  for (i = 0; i < 40; i++) 
    for (j = 0; j < 40; j++) 
      D[i][j] = beta * D[i][j] + B[i][k] * C[k][j];
}
