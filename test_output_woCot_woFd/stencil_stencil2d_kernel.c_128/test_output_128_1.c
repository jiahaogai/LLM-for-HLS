- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide the iterations of the loop `stencil_label3` into chunks of size 8.

#pragma ACCEL kernel