#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 410; r++) {
    tmp[r] = 0.0;
    y[r] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{4}
    for (q = 0; q < 390; q++) {
      tmp[r] = tmp[r] + A[q][r] * x[q];
    }
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{10}
    for (q = 0; q < 390; q++) {
      y[r] = y[r] + A[q][r] * x[q];
    }
  }
}