

Ensure the following loop is not distributed further but executed in the CPU:
```c
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (j = 1; j < 120; j++) {
      y[j] = y[j] + z[j];
    }
```

Ensure the following loop is not distributed further but executed in the CPU:
```c
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 1; i < 40; i++) {
      x[i] = x[i] + y[i];
    }
```

