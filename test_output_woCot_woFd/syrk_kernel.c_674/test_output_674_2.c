- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently, with a factor of 4.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute loop iterations concurrently, with a factor of 8.

#pragma ACCEL kernel