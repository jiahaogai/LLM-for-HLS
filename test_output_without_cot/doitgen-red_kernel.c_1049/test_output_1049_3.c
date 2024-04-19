#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    for (q = 0; q < 30; q++) {
      sum_tmp += A[r][0][q] * C4[q][r];
    }
    sum[r] = sum_tmp;
    for (s = 0; s < 20; s++) {
      tmp = 0.0;
      for (q = 0; q < 30; q++) {
        tmp += A[r][s][q] * sum[q];
      }
      A[r][s][0] = tmp;
    }
  }
}