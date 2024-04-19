#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
  for (tj = 0; tj < 30; tj++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
    for (tk = 0; tk < 30; tk++) {
      sum_tmp += A[0][0][tk] * C4[tk][tj];
    }
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L2}
    for (ti = 0; ti < 25; ti++) {
      sum[tj] += A[ti][0][0] * sum_tmp;
    }
  }
}