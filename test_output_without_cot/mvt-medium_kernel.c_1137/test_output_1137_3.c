#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][50],double x[50],double y_1[40],double y_2[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    y_1[i] = ((double )0);
    y_2[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{4}
    for (j = 0; j < 50; j++) {
      y_1[i] += A[i][j] * x[j];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      y_2[i] += A[j][i] * y_1[j];
    }
  }
}