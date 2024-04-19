#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      sum_tmp_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp_tmp FACTOR=auto{1}
      for (p = 0; p < 25; p++) {
        sum_tmp_tmp += A[p][q][r] * C4[p][r];
      }
      sum_tmp += sum_tmp_tmp;
    }
    sum[r] = sum_tmp;
  }
}