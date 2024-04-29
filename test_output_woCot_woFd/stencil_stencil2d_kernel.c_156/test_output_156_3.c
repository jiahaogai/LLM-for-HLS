- Inside the inner loop:
    - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the loop iterations sequentially, not concurrently.

#pragma ACCEL kernel