#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x[400],double y[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{10}
    for (j = 0; j < 400; j++) {
      x[i] += A[i][j] * y[j];
    }
  }
}