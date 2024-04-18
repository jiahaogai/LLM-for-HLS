#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,double A[250][250],double x1[250],double x2[250],double y_1[250],double y_2[250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    x1[i] = 0.0;
    y_1[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (j = 0; j < 250; j++) {
      x1[i] += A[i][j] * y_2[j];
      y_1[i] += A[i][j] * x2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    x2[i] = 0.0;
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 250; j++) {
      x2[i] += A[i][j] * x1[j];
      y_2[i] += A[i][j] * y_1[j];
    }
  }
}