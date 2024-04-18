#pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
  {
    int i;
    int j;
    double tmp;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction FACTOR=auto{6}
      for (j = 0; j < 400; j++) {
        tmp += A[i][j] * y_1[j];
      }
      x1[i] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
      for (j = 0; j < 400; j++) {
        tmp += A[j][i] * x1[j];
      }
      x2[i] = tmp;
    }
  }