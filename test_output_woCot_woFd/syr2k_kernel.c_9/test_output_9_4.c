- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Parallelize the inner loop.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Parallelize the outer loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Do not tile the inner loop.
- `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline the loop.
- `#pragma ACCEL TILE FACTOR=auto{80}`: Divide the loop into tiles of size 80.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Parallelize the inner loop.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Parallelize the outer loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Do not tile the inner loop.

#pragma ACCEL kernel