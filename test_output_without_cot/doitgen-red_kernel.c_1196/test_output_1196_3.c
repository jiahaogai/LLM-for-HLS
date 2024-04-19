#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

  
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
  for (r = 0; r < 30; r++) {
    sum_tmp = sum[r];
    
#pragma ACCEL PARALLEL reduction=C4_tmp FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      C4_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=A_row_tmp FACTOR=auto{1}
      for (i = 0; i < 25; i++) {
        A_row_tmp = A[i][r];
        C4_tmp += A_row_tmp * B[i][q];
      }
      C4[r][q] = C4_tmp;
    }
    sum[r] = sum_tmp + C4_tmp;
  }
}