#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
      for (j = 0; j < 400; j++) {
        tmp += A[i][j] * y_1[j];
      }
      x1[i] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
      for (j = 0; j < 400; j++) {
        tmp += A[i][j] * y_2[j];
      }
      x2[i] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  }