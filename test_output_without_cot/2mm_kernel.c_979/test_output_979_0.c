13. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline the fourth inner loop.
14. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the fourth inner loop whole, without dividing it into smaller parts.
15. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute the fourth inner loop iterations sequentially, not concurrently.