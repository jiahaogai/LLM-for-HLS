#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL PIPELINE auto{flatten}
  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
    for (i = 0; i < 25; i++) {
      sum_tmp += A[i][0][r] * C4[i][r];
    }
	
    sum[r] = sum_tmp;
  }
}