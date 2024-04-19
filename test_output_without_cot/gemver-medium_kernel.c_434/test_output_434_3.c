#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
  - Parallelize the loop with reduction variable y and a factor determined automatically.

#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1}
  - Parallelize the loop with reduction variable z and a factor determined automatically.

#pragma ACCEL PARALLEL FACTOR=auto{1}
  - Automatically parallelize this loop with a factor determined automatically.