#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][30],double x1[40],double x2[30],double y_1[40],double y_2[30])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    y_1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 30; j++) {
      y_1[i] += A[i][j] * x1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 30; i++) {
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L3}
    for (j = 0; j < 40; j++) {
      y_2[i] += A[j][i] * x2[j];
    }
  }
}