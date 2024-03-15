  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 30; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 120; i++) {
      b[i] = 0.0;
      si = i - 1;
      sj = i;
      sk = i + 1;
      b[i] = a[i] + a[si] + a[sj] + a[sk] + a[sj - 1] + a[sk - 1] + a[sk + 1];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 120; i++) {
      a[i] = 0.33333 * b[i];
    }
  }
}
