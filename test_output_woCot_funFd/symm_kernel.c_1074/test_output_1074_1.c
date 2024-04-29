Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{10}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{20}
Code: #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
Code: #pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
Code: int i;
Code: int j;
Code: int k;
Code: double mult;
Code: double temp1 = 0.0;
Code: double temp2 = 0.0;
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{10}
Code: for (i = 0; i < 60; i++) {
Code:   #pragma ACCEL PIPELINE auto{}
Code:   #pragma ACCEL TILE FACTOR=auto{1}
Code:   #pragma ACCEL PARALLEL FACTOR=auto{20}
Code:    for (j = 0; j < 80; j++) {
Code:      temp1 = 0.0;
Code:      #pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{4}
Code:      for (k = 0; k < 60; ++k) {
Code:        mult = A[i * 60 + k] * B[k * 80 + j];
Code:        temp1 += mult;
Code:      }
Code:      temp2 = alpha * temp1 + beta * C[i * 80 + j];
Code:      C[i * 80 + j] = temp2;
Code:    }
Code: }