5. "Don't automatically distribute this loop onto multiple processors":
```c
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (t = 0; t < 40; t++) {
  jacobi_1d(tsteps,n,A,B);
}

```

6. "Don't automatically distribute this loop onto multiple processors":
```c
#pragma ACCEL PARALLEL FACTOR=auto{2}
for (t = 0; t < 40; t++) {
  jacobi_1d(tsteps,n,B,A);
}

```