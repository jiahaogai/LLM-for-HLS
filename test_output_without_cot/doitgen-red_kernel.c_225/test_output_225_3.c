#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}

    for (q = 0; q < 20; q++) {
      for (s = 0; s < 25; s++) {
        sum_tmp += A[s][q][r] * C4[q][r];
      }
    }

    sum[r] = sum_tmp;
  }
}