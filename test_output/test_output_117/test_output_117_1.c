

5. "This loop has no parallelized version":
```c
  for (t = 0; t < 40; t++) {
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
  }
```