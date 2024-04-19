#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][400],double x[400],double y[400],double tmp[400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    tmp[i] = 0.0;
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{10}
    for (k = 0; k < 400; k++) {
      tmp[i] += A[i][k] * x[k];
    }
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      y[i] += A[i][j] * tmp[j];
    }
  }
//#pragma endscop
}