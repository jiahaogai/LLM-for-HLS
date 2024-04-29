Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{8}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.

#pragma ACCEL kernel
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.

#pragma ACCEL kernel
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{flatten}`: Flatten this loop.
- `#pragma ACCEL TILE FACTOR=auto{2}`: Tile this loop, with 2 blocks per row.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Pad this loop to avoid false sharing.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute loop iterations concurrently, not sequentially.
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Pad this loop to avoid false sharing.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{8}`: Tile this loop, with 8 blocks per row.