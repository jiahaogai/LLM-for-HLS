plaintext
 
#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    y_1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y_1 FACTOR=auto{10}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * x1[j];
    }
    y_1[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp += A[j][i] * x2[j];
    }
    y_2[i] = tmp;
  }
}