- `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loop iterations to maximize parallelism.
- `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations sequentially, not concurrently, with a factor of 1.

#pragma ACCEL kernel