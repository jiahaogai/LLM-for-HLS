#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

  for (i = 0; i < 40; i++) {
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      for (k = 0; k < 60; ++k) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

  for (i = 0; i < 40; i++) {
    for (j = 0; j < 70; j++) {
      F[i][j] = 0.0;
      for (k = 0; k < 50; ++k) {
        F[i][j] += E[i][k] * C[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

  for (i = 0; i < 50; i++) {
    for (j = 0; j < 80; j++) {
      G[i][j] = 0.0;
      for (k = 0; k < 60; ++k) {
        G[i][j] += F[k][i] * D[k][j];
      }
    }
  }