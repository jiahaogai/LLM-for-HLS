- '#pragma ACCEL TILE FACTOR=auto{1}': Keep the loop whole, without dividing it into smaller parts automatically.
- '#pragma ACCEL PIPELINE auto{off}': Do not automatically pipeline the outermost loop.
- '#pragma ACCEL TILE FACTOR=auto{1}': Keep the loop whole, without dividing it into smaller parts automatically.
- '#pragma ACCEL PARALLEL FACTOR=auto{1}': Execute loop iterations sequentially, not concurrently.