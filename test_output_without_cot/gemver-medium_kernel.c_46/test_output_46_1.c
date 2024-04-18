5. The fifth loop multiplies matrix `A` with vector `y` and accumulates the result in vector `z`.
    - `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute loop iterations concurrently with a factor of 8.
    - `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{2}`: Perform reduction operation for variable `z` with a factor of 2.

#pragma ACCEL kernel