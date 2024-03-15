  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 30; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 120; i++) {
      b[i] = 0.0;
      si = i - 1;
      bi = i;
      bp = i + 1;
      sum = a[si] + a[bi] + a[bp];
      b[i] = 0.333333333333333333333333333 * sum;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 120; i++) {
      a[i] = b[i];
    }
  }
}
