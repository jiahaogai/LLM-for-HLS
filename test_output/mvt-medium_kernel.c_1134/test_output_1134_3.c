#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp = A[i][j];
      sum += tmp * x1[j];
    }
    y_1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp = A[j][i];
      sum += tmp * x2[j];
    }
    y_2[i] = sum;
  }
}