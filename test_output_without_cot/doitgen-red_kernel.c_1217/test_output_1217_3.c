#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{25}

  for (r = 0; r < 25; r++) {
    for (q = 0; q < 30; q++) {
      sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
      for (s = 0; s < 20; s++) {
        sum_tmp += A[r][s][q] * C4[s][q];
      }
      sum[r] = sum_tmp;
    }
  }
}