#pragma ACCEL kernel

void kernel_mvt(double A[4][5],double x[5],double y_1[4],double y_2[5])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL reduction = x FACTOR=auto{32}
    for (j = 0; j < 5; j++) {
      x[j] += A[i][j] * y_1[i];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 5; i++) {
    
#pragma ACCEL PARALLEL reduction = y_2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 4; j++) {
      y_2[j] += A[j][i] * x[i];
    }
  }
}