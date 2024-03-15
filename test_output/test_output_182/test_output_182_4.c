
  for (r = 0; r < 32; r++) {
    for (q = 0; q < 32; q++) {
      tmp = ((double )0);
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 0; p < 32; p++) {
        tmp += A[r][p] * B[p][q];
      }
      C[r][q] = tmp;
    }
  }
}
