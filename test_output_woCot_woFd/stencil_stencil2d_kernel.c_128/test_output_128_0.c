- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the loop `stencil_label3` sequentially, not concurrently.

#pragma ACCEL kernel