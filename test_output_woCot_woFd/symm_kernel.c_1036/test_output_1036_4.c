8. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
9. `#pragma ACCEL TILE FACTOR=auto{80}` - Keep the outer loop whole, without dividing it into smaller parts.
10. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute outer loop iterations sequentially, not concurrently.
11. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the inner loop.
12. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the inner loop whole, without dividing it into smaller parts.
13. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute inner loop iterations in parallel with a factor of 4.