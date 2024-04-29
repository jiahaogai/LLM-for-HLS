- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts to maintain data locality.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the loop iterations sequentially (not concurrently) to prevent race conditions and maintain correctness.

#pragma ACCEL kernel