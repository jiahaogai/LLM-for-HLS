#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y1[400],double y2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x1[i] = 0.0;
    y1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x2[i] = 0.0;
    y2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * x2[j];
      y1[i] += A[i][j] * y2[j];
    }
  }
}