Inside the inner loop:
1. `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}`: The `C` variable is a reduction variable and needs to be parallelized with a parallelization factor of 8.

#pragma ACCEL kernel