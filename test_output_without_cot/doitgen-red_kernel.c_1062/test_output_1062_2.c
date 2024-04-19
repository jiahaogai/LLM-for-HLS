#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (i = 0; i < 30; i++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}

    for (j = 0; j < 20; j++) {
      for (k = 0; k < 25; k++) {
        sum_tmp += A[k][j][i] * C4[k][j];
      }
    }

    sum[i] = sum_tmp;
  }
}