#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,double A[250][250],double x1[250],double y1[250],double x2[250],double y2[250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    x1[i] = 0.0;
    y1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    for (j = 0; j < 250; j++) {
      x1[i] = x1[i] + A[i][j] * y2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 250; i++) {
    y1[i] = 0.0;
    for (j = 0; j < 250; j++) {
      y1[i] = y1[i] + A[j][i] * x2[j];
    }
  }
}