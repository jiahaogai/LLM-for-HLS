### ACCEL PIPELINE auto{off}
 
#pragma ACCEL PIPELINE auto{off}


### ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL TILE FACTOR=auto{1}


### ACCEL PARALLEL FACTOR=auto{12}
 
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for(i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for(j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for(j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}