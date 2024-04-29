Code: #pragma ACCEL PIPELINE auto{off}
 #pragma ACCEL TILE FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{4}
    for (j = 0; j < 60; j++) {
      A[i][j] *= beta;
      A[i][j] += alpha * P[i][0] * Q[j][0];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for (j = 0; j < 60; j++) {
      Q[i][j] *= beta;
      Q[i][j] += alpha * P[i][0] * A[j][0];
    }
  }
}