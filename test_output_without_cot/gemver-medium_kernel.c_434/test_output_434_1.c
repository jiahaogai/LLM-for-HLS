#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
  - Parallelize the loop with reduction variable y and a factor determined automatically.

#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1}
  - Parallelize the loop with reduction variable z and a factor determined automatically.

#pragma ACCEL PIPELINE auto{off}
  - Do not automatically pipeline this loop.

#pragma ACCEL PARALLEL FACTOR=auto{1}
  - Execute loop iterations sequentially, not concurrently.