Code: #pragma ACCEL PIPELINE auto{}`: Automatically pipeline the loop
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently in groups of 4
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently in groups of 4

For the outer loop:
- `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline the loop
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations concurrently in groups of 1