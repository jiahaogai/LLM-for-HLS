#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{25}

  for (tj = 1; tj < 20 - 1; tj++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}

    for (tk = 1; tk < 30 - 1; tk++) {
      sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
      for (ti = 0; ti < 25; ti++) {
        sum_tmp += A[ti][aj][ak] * C4[tk][aj];
      }
      sum[tk] = sum_tmp;
    }
    ak = 1;
  }
  aj = 1;
}