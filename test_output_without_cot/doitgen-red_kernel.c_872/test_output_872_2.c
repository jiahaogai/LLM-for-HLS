#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

  
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
  for (i = 0; i < 30; i++) {
    sum_tmp = sum[i];
    
#pragma ACCEL PARALLEL reduction=C4_tmp FACTOR=auto{32}
    for (j = 0; j < 30; j++) {
      C4_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=A_tmp FACTOR=auto{1}
      for (k = 0; k < 20; k++) {
        A_tmp = A[i][k][j];
        C4_tmp += A_tmp * k;
      }
      C4[i][j] = C4_tmp;
    }
    sum[i] = sum_tmp + C4_tmp;
  }
}