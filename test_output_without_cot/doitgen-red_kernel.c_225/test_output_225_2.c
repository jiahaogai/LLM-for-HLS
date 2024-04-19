#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (i = 0; i < 30; i++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}

    for (j = 0; j < 25; j++) {
      for (k = 0; k < 20; k++) {
        sum_tmp += A[j][k][i] * C4[k][i];
      }
    }

    sum[i] = sum_tmp;
  }
}