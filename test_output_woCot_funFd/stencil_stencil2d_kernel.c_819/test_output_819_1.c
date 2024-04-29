Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute loop iterations concurrently, not sequentially.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide each iteration of this loop into eight smaller partitions which are executed concurrently.

#pragma ACCEL kernel
 
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
for (i = 0; i < 8192; i++) {
  orig[i] = i;
}
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 8192; i++) {
  sol[i] = ((filter[0] * orig[i - 8192 * 0]) + (filter[1] * orig[i - 8192 * 1]) + (filter[2] * orig[i - 8192 * 2]) + (filter[3] * orig[i - 8192 * 3]) + (filter[4] * orig[i - 8192 * 4]) + (filter[5] * orig[i - 8192 * 5]) + (filter[6] * orig[i - 8192 * 6]) + (filter[7] * orig[i - 8192 * 7]) + (filter[8] * orig[i - 8192 * 8])) / 8192.0;
}
}