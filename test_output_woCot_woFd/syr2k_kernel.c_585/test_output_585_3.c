**#pragma ACCEL PIPELINE auto{off}**

**#pragma ACCEL TILE FACTOR=auto{1}**

**#pragma ACCEL PARALLEL FACTOR=auto{2}**

**#pragma ACCEL PARALLEL FACTOR=auto{80}**

**#pragma ACCEL PARALLEL FACTOR=auto{60}**

**#pragma ACCEL PARALLEL FACTOR=auto{5}**
 #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for(i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for(j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for(k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{5}
      for(j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}