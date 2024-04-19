#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}

  for (r = 0; r < 30; r++) {
    for (s = 0; s < 30; s++) {
      sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (q = 0; q < 20; q++) {
        sum_tmp += A[r][q][s] * C4[q][s];
      }
      sum[r] = sum_tmp;
    }
  }
}