Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{60}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{10}
Code: #pragma ACCEL name=L1
Code: 
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
        tmp = 0.0;
        for (k = 0; k < 60; k++) {
           tmp += A[i][k] * B[k][j];
        }
        C[i][j] = tmp;
     }
  }
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{80}
Code: #pragma ACCEL name=L2
Code: 
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
     tmp = 0.0;
     for (j = 0; j < 80; j++) {
        tmp += A[i][j] * C[j][i];
     }
     sum = 0.0;
     for (j = 0; j < 60; j++) {
        sum += A[j][i] * tmp;
     }
     printf("%f\n",sum);
  }