#pragma ACCEL kernel

void kernel_mvt(double x1[4096],double x2[4096],double y_1[4096],double y_2[4096],double A[4096][4096])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4096; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 4096; i++) {
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{4}
    for (j = 0; j < 4096; j++) {
      x1[j] += A[i][j] * y_1[i];
      x2[i] += A[i][j] * y_2[j];
    }
  }
}