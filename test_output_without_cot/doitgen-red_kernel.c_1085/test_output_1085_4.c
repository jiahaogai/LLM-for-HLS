5. `#pragma ACCEL PIPELINE auto{__PIPE__L2}` - Do not automatically pipeline this loop.
6. `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}` - Divide this loop into smaller parts with a factor of 30.
7. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}` -