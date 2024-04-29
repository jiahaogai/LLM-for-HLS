Inside the inner loop:
1. `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}`: Distribute the reduction of `C` among 4 processes.

#pragma ACCEL kernel