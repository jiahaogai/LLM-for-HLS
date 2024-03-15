
  for (p = 0; p < 32; p++) {
    for (r = 0; r < 32; r++) {
      tmp = A[r] * B[p];
      C[p] += tmp;
    }
  }
}
