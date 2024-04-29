Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 200; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 240; j++) {
    C[i][j] *= beta;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 200; k++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      C[i][j] += alpha * A[i][k] * B[k][j];
    }
  }
}
//#pragma endscop
}