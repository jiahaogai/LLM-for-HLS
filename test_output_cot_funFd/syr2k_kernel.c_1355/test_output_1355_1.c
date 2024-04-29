#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    for (k = 0; k < 60; k++) {
      A[i][k] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (j = 0; j < 80; j++) {
        B[k][j] *= alpha;
        C[i][j] += A[i][k] * B[k][j];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 0; j < 80; j++) {
        C[i][j] += B[i][k] * A[k][j];
      }
    }
  }
}