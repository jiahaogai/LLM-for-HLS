#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][400],double B[400][400],double x[400],double y[400],double tmp[400][400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{12}
    for (j = 0; j < 400; j++) {
      x1 = 0.0;
      for (k = 0; k < 400; k++) {
        x1 += A[i][k] * B[k][j];
      }
      tmp[i][j] = x1;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{120}
    for (j = 0; j < 400; j++) {
      x2 = 0.0;
      for (k = 0; k < 400; k++) {
        x2 += tmp[i][k] * B[k][j];
      }
      y[i] = x2;
    }
  }
//#pragma endscop
}