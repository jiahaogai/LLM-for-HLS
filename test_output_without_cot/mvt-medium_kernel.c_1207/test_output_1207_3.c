#pragma ACCEL kernel

void kernel_mvt(double x1[4096], double x2[4096], double y_1[4096], double y_2[4096], double A[4096][4096])
  ;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (int i = 0; i < 4096; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (int i = 0; i < 4096; i++) {
    x2[i] = 0.0;
    for (int j = 0; j < 64; j++) {
      x2[i] += A[i * 64][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (int i = 0; i < 4096; i++) {
    y_2[i] = 0.0;
    for (int j = 0; j < 64; j++) {
      y_2[i] += A[i * 64][j] * x1[j];
    }
  }
}