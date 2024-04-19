#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 400; r++) {
     x1[r] = 0.0;
     x2[r] = 0.0;
     for (c = 0; c < 400; c++) {
       x1[r] = x1[r] + A[r][c] * y_1[c];
     }
     for (c = 0; c < 400; c++) {
       x2[r] = x2[r] + A[r][c] * y_2[c];
     }
  }
}