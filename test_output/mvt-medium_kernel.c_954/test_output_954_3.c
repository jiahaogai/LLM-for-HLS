c
 #pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    int j_row;
    
#pragma ACCEL PARALLEL FACTOR=auto{15}
    for (j = 0; j < 400; j++) {
      j_row = 0;
      j_row = j;
      x1[j_row] += A[i][j] * y_2[j];
    }
    y_1[i] = x1[i] + y_1[i];
  }
}