#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 400; i++) {
    double sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{10}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * y_1[j];
    }
    x1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 400; i++) {
    x2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 400; i++) {
    double sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * y_2[j];
    }
    x2[i] = sum;
  }
}