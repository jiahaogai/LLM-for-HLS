- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the following loop for `y_1` calculation.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the following loop whole without dividing it into smaller parts for `y_1` calculation.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently with a factor of 4 for `y_1` calculation.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the following loop for `y_2` calculation.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the following loop whole without dividing it into smaller parts for `y_2` calculation.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently with a factor of 4 for `y_2` calculation.

#pragma ACCEL kernel