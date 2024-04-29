- `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the loop whole without dividing it into smaller parts, using an automatically determined tiling factor.
    - `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a parallel factor of 1, for no additional parallelism.

#pragma ACCEL kernel