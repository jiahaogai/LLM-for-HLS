- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`: Make the outer loop of this loop parallel.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}`: Make the middle loop of this loop parallel.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}`: Make the inner loop of this loop parallel.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}`: Make the outermost loop of this loop parallel.

#pragma ACCEL kernel