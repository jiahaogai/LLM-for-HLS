#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][500],double B[400][500],double x[500],double y[400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x FACTOR=auto{1}
    for (j = 0; j < 500; j++) {
      x[j] = 0.0;
      for (k = 0; k < 500; ++k) {
        x[j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = y FACTOR=auto{8}
    for (j = 0; j < 500; j++) {
      y[i] += x[j] * A[i][j];
    }
  }
//#pragma endscop
}