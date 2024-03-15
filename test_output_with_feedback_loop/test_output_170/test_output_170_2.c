#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (j = 16; j < 96; j++) {
    tmp = 0.0;
    dum = 0.0;
    for (i = 1; i < 80; i++) {
      tmp += A[i][j];
      dum += A[i][j] * B[i][j];
    }
    for (i = 1; i < 80; i++) {
      A[i][j] = A[i][j] - tmp / 80.0;
      B[i][j] = B[i][j] - A[i][j] * dum / tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 1; i < 80; i++) {
    y[i] = 0.0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (j = 16; j < 96; j++) {
    sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L4}
    for (i = 1; i < 80; i++) {
      sum += A[i][j] * y[i];
    }
    
#pragma ACCEL PIPELINE auto{off}
    y[j] = sum;
  }
}