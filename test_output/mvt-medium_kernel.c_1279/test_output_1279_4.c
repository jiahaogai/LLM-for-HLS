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
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{120}
    for (j = 0; j < 400; j++) {
      j_col = A[i][j];
      sum += j_col * x1[j];
    }
    y_1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    int i_row;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      i_row = A[j][i];
      sum += i_row * x2[j];
    }
    y_2[i] = sum;
  }
}