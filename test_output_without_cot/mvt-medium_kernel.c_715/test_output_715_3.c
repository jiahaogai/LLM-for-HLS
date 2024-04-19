#pragma ACCEL kernel

void kernel_mvt(int m,int n,double A[40][30],double x1[40],double x2[30],double y_1[40],double y_2[30])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
    for (j = 0; j < 30; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 30; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{10}
    for (j = 0; j < 40; j++) {
      x2[i] += A[j][i] * y_2[j];
    }
  }
}