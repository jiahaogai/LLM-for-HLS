#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 1; j <= n; j++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L3}
    for (i = 1; i <= n - 1; i++) {
      A[i][j] = A[i][j] - A[i][1] * A[1][j];
    }
  }
}