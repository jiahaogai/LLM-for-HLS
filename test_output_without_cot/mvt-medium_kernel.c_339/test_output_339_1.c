#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][40],double x1[40],double x2[40],double y_1[40],double y_2[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{5}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 40; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    x2[i] = ((double )0);
  }
  
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{8}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 40; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}