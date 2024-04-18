#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    int j_j;
    double y_1_i;
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{4}
    for (j = 0; j < 400; j++) {
      j_j = j;
      y_1_i = y_1[j_j];
      x1[i] += A[i][j] * y_1_i;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    int j_j;
    double y_2_i;
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{24}
    for (j = 0; j < 400; j++) {
      j_j = j;
      y_2_i = y_2[j_j];
      x2[i] += A[j][i] * y_2_i;
    }
  }
}