#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][40],double x[40],double y_1[40],double y_2[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    y_1[i] = 0.0;
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{6}
    for (j = 0; j < 40; j++) {
      y_1[i] += A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 40; i++) {
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      y_2[i] += A[j][i] * x[j];
    }
  }
}