 

#pragma ACCEL PIPELINE auto{__PIPE__L0}

#pragma ACCEL TILE FACTOR=auto{__TILE__L0}

#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 16; j < 24; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 16; i < 24; i++) {
      C[j][i] = C[j][i] + B[j][i] * A[i][j];
    }
  }
}
