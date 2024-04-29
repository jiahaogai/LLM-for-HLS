- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the innermost loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute innermost loop iterations concurrently with a factor of 8.

#pragma ACCEL kernel