### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for(i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for(j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{16}
    for(j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}