

5. "Assign this loop to FACTOR=auto{__PARA__L2}":
```c
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (t = 0; t < 40; t++) {
    jacobi_1d(A,B,n);
    jacobi_1d(B,A,n);
  }
```

