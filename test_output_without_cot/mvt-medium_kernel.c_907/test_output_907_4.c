### ACCEL PIPELINE auto{off}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{12}
 
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{15}
    for (i = 0; i < 400; i++) {
      tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
      for (j = 0; j < 400; j++) {
        tmp += A[i][j] * y_1[j];
      }
      x1[i] = tmp;
    }

#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * y_2[j];
    }
    x2[i] = tmp;
  }
}