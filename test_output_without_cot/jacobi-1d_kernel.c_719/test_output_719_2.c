#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{118}
    for (i = 1; i < 118; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (i = 1; i < 32; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
  }
}