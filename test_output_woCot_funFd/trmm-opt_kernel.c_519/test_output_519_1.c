Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{16}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{80}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{80}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
Code: #pragma ACCEL PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{16}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{80}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}