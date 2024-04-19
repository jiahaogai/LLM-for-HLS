#pragma ACCEL kernel

void kernel_mvt(int n,int nP,double A[40][50],double x1[50],double x2[40],double y_1[50],double y_2[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 50; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    y_2[i] = 0.0;
    for (j = 0; j < 50; j++) {
      x1[j] += A[i][j] * y_1[i];
      y_2[i] += A[i][j] * x1[j];
    }
  }
}