- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the innermost loop whole without dividing it into smaller parts, with automatic factor calculation.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute innermost loop iterations concurrently with automatic factor calculation.

#pragma ACCEL kernel