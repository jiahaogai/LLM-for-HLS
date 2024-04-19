- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    for (q = 0; q < 30; q++) {
      sum_tmp = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (s = 0; s < 20; s++) {
        sum_tmp += A[r][s][q] * C4[s][q];
      }
      sum[r] = sum_tmp;
    }
  }
}