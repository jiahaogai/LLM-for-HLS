#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 400; i++) {
    int j_row;
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 400; j++) {
      j_row = i * 400 + j;
      x1[i] += A[j_row] * y_2[j];
    }
    y_1[i] = x1[i];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 400; i++) {
    int j_col;
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 400; j++) {
      j_col = i + j * 400;
      x2[i] += A[j_col] * y_1[j];
    }
  }
}