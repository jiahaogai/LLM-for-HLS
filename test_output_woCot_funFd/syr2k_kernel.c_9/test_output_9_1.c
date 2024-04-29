#pragma ACCEL PIPELINE auto{}
 #pragma ACCEL TILE FACTOR=auto{80}
 #pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{}
 #pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (int i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (int j = 0; j < 60; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (int j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (int k = 0; k < 80; k++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}