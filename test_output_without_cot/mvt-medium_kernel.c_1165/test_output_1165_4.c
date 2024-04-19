### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
  for(i = 0; i < 400; i++) {
    tmp = 0.0;
    for(j = 0; j < 400; j++) {
      tmp += A[i][j] * y_1[j];
    }
    x1[i] = tmp;
  }

### ACCEL PIPELINE auto{}

### ACCEL TILE FACTOR=auto{20}

### ACCEL PARALLEL FACTOR=auto{20}
 
#pragma ACCEL PARALLEL FACTOR=auto{20}
  
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{10}
  for(i = 0; i < 400; i++) {
    tmp = 0.0;
    for(j = 0; j < 400; j++) {
      tmp += A[i][j] * y_2[j];
    }
    x2[i] = tmp;
  }