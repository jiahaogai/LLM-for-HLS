#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (t = 0; t < 30; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 1; i < 119; i++) {
      B[i] = 0.33333 * (A[i] + A[i - 1] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (i = 1; i < 119; i++) {
      A[i] = 0.33333 * (B[i] + B[i - 1] + B[i + 1]);
    }
  }
}