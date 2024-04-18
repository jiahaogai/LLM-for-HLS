#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x[400],double y[400],double tmp[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    tmp[i] = 0.0;
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{4}
    for (j = 0; j < 400; j++) {
      tmp[i] += A[i][j] * x[j];
    }
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      y[i] += A[i][j] * tmp[j];
    }
  }
}