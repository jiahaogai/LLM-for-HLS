#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 1; j <= n; j++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{4}
    for (i = 1; i <= n - 1; i++) {
      y[i] += b[i] * y[j];
    }
  }
}