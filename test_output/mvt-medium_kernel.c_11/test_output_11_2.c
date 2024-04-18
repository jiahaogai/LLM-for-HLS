#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    int j_col;
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j_col = 0; j_col < 400; j_col++) {
      sum += A[i][j_col] * y_1[j_col];
    }
    x1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{120}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    int i_row;
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (i_row = 0; i_row < 400; i_row++) {
      sum += A[i_row][i] * x1[i_row];
    }
    x2[i] = sum;
  }
}