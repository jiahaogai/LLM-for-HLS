### ACCEL PIPELINE auto{off}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for(i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for(i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L3}
    for(j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for(i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L5}
    for(j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}