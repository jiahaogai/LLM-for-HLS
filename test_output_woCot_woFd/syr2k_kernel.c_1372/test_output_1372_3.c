- `#pragma ACCEL PIPELINE auto{off}` (inner loop):
  - Explanation: Do not automatically pipeline this loop. This pragma disables automatic pipelining for the loop following it.

- `#pragma ACCEL TILE FACTOR=auto{1}` (inner loop):
  - Explanation: Keep this loop whole, without dividing it into smaller parts. This pragma sets the tile factor to 1 for the inner loop, meaning the loop should not be tiled into smaller sub-loops.