#pragma ACCEL PIPELINE auto{off}
  - Do not automatically pipeline this loop.

#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
  - Parallelize the loop with reduction variable y and a factor determined automatically.