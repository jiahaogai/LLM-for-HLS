#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{40}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{15}
    for (i = 1; i < 118; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 118; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
  }
}