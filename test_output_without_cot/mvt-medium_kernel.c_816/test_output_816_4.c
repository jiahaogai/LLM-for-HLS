- `#pragma ACCEL PIPELINE auto{off}`:
  - Do not automatically pipeline this loop.

- `#pragma ACCEL TILE FACTOR=auto{1}`:
  - Keep the loop whole without dividing it into smaller parts, with the tile factor automatically determined.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`:
  - Execute loop iterations concurrently with a factor automatically determined.