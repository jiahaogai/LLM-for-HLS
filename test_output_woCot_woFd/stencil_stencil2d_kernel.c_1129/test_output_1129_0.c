- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, with a parallelization factor of 1.

#pragma ACCEL kernel