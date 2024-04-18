#pragma ACCEL kernel

void kernel_mvt(int m,int n,double A[40][30],double x1[40],double x2[30],double y_1[40],double y_2[30])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 40; i++) {
    x1[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{32}
    for (j = 0; j < 30; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 30; i++) {
    x2[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      x2[i] += A[j][i] * y_1[j];
    }
  }
}