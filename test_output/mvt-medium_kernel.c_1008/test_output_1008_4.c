#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = y_1[i];
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x1[j];
    }
    
#pragma ACCEL PARALLEL reduction=y_1 FACTOR=auto{__PARA__L2}
    y_1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    double sum = y_2[i];
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x2[j];
    }
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L7}
    y_2[i] = sum;
  }
}