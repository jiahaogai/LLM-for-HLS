### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for(i = 0; i < 400; i++) {
    x1 = 0.0;
    x2 = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for(j = 0; j < 400; j++) {
      x1 += A[i][j] * y_1[j];
      x2 += A[i][j] * y_2[j];
    }
    x1_1[i] = x1;
    x2_1[i] = x2;
  }
}