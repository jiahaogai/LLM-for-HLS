- `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline the inner loop for parallelization.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the inner loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute the inner loop iterations concurrently with a factor of 8.

#pragma ACCEL kernel