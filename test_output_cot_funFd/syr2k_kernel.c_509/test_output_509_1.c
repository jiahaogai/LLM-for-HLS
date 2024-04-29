#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
     for (j = 0; j < 60; j++) {
       tmp = 0.0;
       for (k = 0; k < 80; k++) {
         tmp += A[i][k] * B[k][j];
       }
       C[i][j] = alpha * tmp + beta * C[i][j];
     }
   }
}