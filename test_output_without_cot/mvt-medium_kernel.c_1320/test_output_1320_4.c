9. `#pragma ACCEL PIPELINE auto{__PIPE__L2}` - Automatically pipeline this loop.
10. `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}` - Divide the loop by tiles.
11. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}` - Execute loop iterations concurrently.
12. `#pragma ACCEL PIPELINE auto{__PIPE__L3}` - Automatically pipeline this loop.
13. `#pragma ACCEL TILE FACTOR=auto{__TILE__L3}` - Divide the loop by tiles.
14. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}` - Execute loop iterations concurrently.