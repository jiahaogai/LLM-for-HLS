c
 #pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}