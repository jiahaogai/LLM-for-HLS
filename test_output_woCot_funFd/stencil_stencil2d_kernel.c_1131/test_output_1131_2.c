Code: #pragma ACCEL PIPELINE auto{flatten}`: Automatically pipeline the loop and flatten the loop hierarchy to improve throughput and reduce latency.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts to maintain data locality.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the loop iterations concurrently with a parallel factor of 1 to maximize parallelism but do not exceed the number of cores provided by the system.

#pragma ACCEL kernel
 
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
stencil_1:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    stencil_2:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      stencil_3:
      for (k = -1; k <= 1; k++) {
        for (l = -1; l <= 1; l++) {
          idx = (i + k) * 8192 + (j + l);
          if (idx < 0 || idx > 65535) {
            continue;
          }
          sum += filter[k + 1][l + 1] * orig[idx];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}