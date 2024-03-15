  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 30; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (i = 1; i <= 120; i++) {
      b[i] = 0.0;
      si = i - 1;
      sj = i - 1;
      double _in_val = A[i];
      b[si] = b[si] + 1.0 * _in_val;
      b[sj] = b[sj] + 1.0 * _in_val;
      b[si + 1] = b[si + 1] + 2.0 * _in_val;
      b[sj + 1] = b[sj + 1] + 2.0 * _in_val;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (i = 1; i <= 120; i++) {
      tmp = b[i];
      A[i] = 0.25 * (b[i - 1] - 2.0 * tmp + b[i + 1]);
    }
  }
}
