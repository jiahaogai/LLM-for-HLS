#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (tj = 1; tj < 30; tj++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
    for (tk = 1; tk < 30; tk++) {
      sum_tmp += A[i][j][tk] * C4[tk][tj];
    }
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L2}
    for (ti = 1; ti < 20; ti++) {
      sum[tj] += A[i][ti][k] * sum_tmp;
    }
  }
}