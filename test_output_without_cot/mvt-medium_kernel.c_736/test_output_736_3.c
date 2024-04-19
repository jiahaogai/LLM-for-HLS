#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][40],double x[40],double y[40],double tmp[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    tmp[i] = 0.0;
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{10}
    for (j = 0; j < 40; j++) {
      tmp[i] = A[i][j] * x[j] + tmp[i];
      y[i] = A[i][j] * x[j] + y[i];
    }
  }
}