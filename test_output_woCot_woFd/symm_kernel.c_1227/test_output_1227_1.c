8. **#pragma ACCEL PIPELINE auto{}**: Automatically pipeline the second inner loop.
9. **#pragma ACCEL TILE FACTOR=auto{1}**: Keep the second inner loop whole without dividing it into smaller parts using a tile factor of 1.
10. **#pragma ACCEL PARALLEL FACTOR=auto{4}**: Execute the second inner loop iterations concurrently with a parallel factor of 4.