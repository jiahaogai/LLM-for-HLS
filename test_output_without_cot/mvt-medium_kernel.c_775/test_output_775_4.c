#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  for (i = 0; i < 400; i++) {
    tmp1 = 0.0;
    tmp2 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * y_2[j];
    }
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{__PARA__L6}
    x1[i] = tmp1;
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{__PARA__L7}
    x2[i] = tmp2;
  }
}