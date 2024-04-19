#pragma ACCEL PARALLEL FACTOR=auto{2}
  
#pragma ACCEL PIPELINE auto{off}
  for (r = 0; r < 400; r++) {
    tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
    for (q = 0; q < 400; q++) {
      tmp += A[r][q] * y_1[q];
    }
    x1[r] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{}
  for (r = 0; r < 400; r++) {
    tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L3}
    for (q = 0; q < 400; q++) {
      tmp += A[q][r] * x1[q];
    }
    x2[r] = tmp;
  }
}