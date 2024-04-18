#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double v1[400],double v2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    y_1[i] = 0.0;
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y_1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      y_1[i] += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      y_2[i] += A[i][j] * v2[j];
    }
  }
}