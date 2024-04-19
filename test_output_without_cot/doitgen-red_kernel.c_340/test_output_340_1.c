- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      tmp += A[r][0][q] * C4[q][0];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (s = 0; s < 20; s++) {
      _sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=_sum FACTOR=auto{1}
      for (q = 0; q < 30; q++) {
        _sum += A[r][s][q] * C4[q][s];
      }
      sum[s] = tmp * _sum;
    }
    for (s = 0; s < 20; s++) {
      A[r][s][0] = sum[s];
    }
  }
}