Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{16}
Code: #  ifdef ALPHA
Code:   alpha
Code: #  else
Code:   1.0
Code: #  endif
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{16}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Code:   C[i][j] *= beta;
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code:   C[i][j] +=  A[i][k] * B[k][j];
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code:   C[i][j] *= alpha;