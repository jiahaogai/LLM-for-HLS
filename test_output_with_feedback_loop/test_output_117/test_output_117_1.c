5. "Process this loop with Unroll(auto)":
```c
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 30; t++) {
    #pragma ACCEL PIPELINE auto{__PIPE__L2}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
    #pragma ACCEL PIPELINE auto{__PIPE__L3}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
  }
```