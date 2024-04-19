#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    tmp1 = 0.0;
    tmp2 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * y_2[j];
    }
    x1[i] = tmp1;
    x2[i] = tmp2;
  }
}