
 #pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 1; j <= n; j++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L2}
    for (i = j; i <= n; i++) {
      A[i][j] = A[i][j] - A[i][1] * A[j][1] - A[i][2] * A[j][2];
    }
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L3}
    for (i = j; i <= n; i++) {
      A[i][j] = A[i][j] / A[j][j];
    }
  }
}
