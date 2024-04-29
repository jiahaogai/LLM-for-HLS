8. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
9. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
10. `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.

#pragma ACCEL kernel