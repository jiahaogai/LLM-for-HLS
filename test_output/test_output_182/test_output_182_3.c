
  for (p = 0; p < 32; p++) {
    for (r = 0; r < 32; r++) {
      tmp = A[p][r];
      B[p][r] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (q = 0; q < 32; q++) {
        B[p][r] += tmp * C[p][q] * D[q][r];
      }
    }
  }
}
