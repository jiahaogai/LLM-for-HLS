- `#pragma ACCEL PARALLEL reduction=y FACTOR=auto{8}`: Parallelize loop iterations, performing a reduction operation on variable y with a factor of 8.
- `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1}`: Parallelize loop iterations, performing a reduction operation on variable z with a factor of 1.

#pragma ACCEL kernel