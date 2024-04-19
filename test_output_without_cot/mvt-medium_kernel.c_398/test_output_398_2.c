### ACCEL PIPELINE auto{off}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}