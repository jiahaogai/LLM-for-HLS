4. `#pragma ACCEL PIPELINE auto{}`: Do not automatically pipeline this loop.
5. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
6. `#pragma ACCEL PARALLEL FACTOR=auto{5}`: Execute loop iterations in parallel, with a factor of 5.
7. `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations in parallel, with a factor of 4.

#pragma ACCEL kernel