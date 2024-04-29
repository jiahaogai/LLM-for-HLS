Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{10}
for (i = 0; i < 60; i++) {
   for (j = 0; j < 80; j++) {
      C[i][j] = 0.0;
      for (k = 0; k < 60; k++) {
         C[i][j] += alpha * A[i][k] * B[k][j];
      }
   }
}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{20}
for (i = 0; i < 60; i++) {
   for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      for (k = 0; k < 80; k++) {
         temp2 += B[i][k] * C[k][j];
      }
      temp1 = alpha * temp2 + beta * C[i][j];
      C[i][j] = temp1;
   }
}