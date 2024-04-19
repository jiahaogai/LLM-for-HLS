#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{120}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = 0.0;
    y_1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    y_2[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      y_2[i] += A[i][j] * x1[j];
      x2[i] += A[i][j] * y_1[j];
    }
  }
}