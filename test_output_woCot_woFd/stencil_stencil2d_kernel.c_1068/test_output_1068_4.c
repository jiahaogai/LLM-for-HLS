- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop (`stencil_label3`) whole, without dividing it into smaller parts, to optimize memory access patterns.
     - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute iterations of this loop (`stencil_label3`) in parallel on 1 hardware processing unit to exploit parallelism.

#pragma ACCEL kernel