- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts, to optimize memory access patterns.
     - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute iterations of this loop in parallel on 1 hardware processing unit to exploit parallelism.

#pragma ACCEL kernel