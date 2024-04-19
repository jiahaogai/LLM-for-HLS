#pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 40; i++) {
  for (j = 0; j < 50; j++) {
    tmp[i][j] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (k = 0; k < 70; ++k) {
      tmp[i][j] += alpha * A[i][k] * B[k][j];
    }
  }
}
 
#pragma ACCEL PIPELINE auto{}
 
#pragma ACCEL TILE FACTOR=auto{8}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 40; i++) {
  for (j = 0; j < 80; j++) {
    D[i][j] *= beta;
    
#pragma ACCEL PARALLEL FACTOR=auto{25}
    for (k = 0; k < 50; ++k) {
      D[i][j] += tmp[i][k] * C[k][j];
    }
  }
}