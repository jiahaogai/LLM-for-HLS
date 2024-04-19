#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y1[400],double y2[400],double A[400][400],double B[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{10}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{5}
    for (j = 0; j < 400; j++) {
      x2[i] += B[i][j] * y2[j];
    }
  }
}