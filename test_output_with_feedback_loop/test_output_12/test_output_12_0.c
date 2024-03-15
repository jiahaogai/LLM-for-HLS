#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 16; j < 24; j++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L3}
    for (i = 1; i < 20; i++) {
      A[j][i] = A[j][i] - A[j][i - 1] * B[j][i - 1];
    }
  }
}