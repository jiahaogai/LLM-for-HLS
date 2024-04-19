#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
    for (q = 0; q < 25; q++) {
      sum_tmp += A[q][r][s] * C4[s][r];
    }
    
    sum[r] = sum_tmp;
  }
}