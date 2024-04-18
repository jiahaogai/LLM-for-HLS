#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,double A[400][400],double x1[400],double x2[400],double y1[400],double y2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x2[i] += A[j][i] * y2[j];
    }
  }
}