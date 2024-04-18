#pragma ACCEL kernel
  
  void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
  {
    int i;
    int j;
    double tmp;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    kernel_mvt_1:
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{3}
      kernel_mvt_2:
      for (j = 0; j < 400; j++) {
        tmp += A[i][j] * y_1[j];
      }
      x1[i] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    kernel_mvt_3:
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      kernel_mvt_4:
      for (j = 0; j < 400; j++) {
        tmp += A[j][i] * y_2[j];
      }
      x2[i] = tmp;
    }
  }