#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][400],double B[400][400],double x[400],double y[400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x FACTOR=auto{12}
    for (j = 0; j < 400; j++) {
      x[i] += A[i][j] * B[j][i];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = y FACTOR=auto{1}
    for (k = 0; k < 400; k++) {
      y[i] += A[i][k] * x[k];
    }
  }
//#pragma endscop
}