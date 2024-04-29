Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: double sum = 0.0;
Code: for(k = 0;k < 60;k++) {
Code: sum = sum + A[i][k] * B[k][j];
Code: }
Code: C[i][j] = alpha * sum;