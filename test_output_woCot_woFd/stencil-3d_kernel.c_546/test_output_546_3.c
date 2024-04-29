- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the middle loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the outer loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the innermost loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the middle loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the outer loop, using a parallelization factor of 16.

- `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline the outermost loop to increase throughput.

- `#pragma ACCEL TILE FACTOR=auto{2}`: Divide the outer loop into smaller parts to facilitate parallelism.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the innermost loop iterations sequentially, not concurrently.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the middle loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the outer loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the innermost loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the middle loop, using a parallelization factor of 16.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Parallelize the outer loop, using a parallelization factor of 16.

- `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline the outermost loop to increase throughput.

- `#pragma ACCEL TILE FACTOR=auto{2}`: Divide the outer loop into smaller parts to facilitate parallelism.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the innermost loop iterations sequentially, not concurrently.

- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Parallelize the middle loop, using a parallelization factor of 8.

- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Parallelize the outer loop, using a parallelization factor of 8.

- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Parallelize the innermost loop, using a parallelization factor of 8.

- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Parallelize the middle loop, using a parallelization factor of 8.

- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Parallelize the outer loop, using a parallelization factor of 8.

#include <math.h>
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1; i++) {
        i_col = i - 1 + ((32 + 4) * (k - 1));
        j_col = j - 1 + ((32 + 4) * (32 + 4));
        k_col = k - 1 + ((32 + 4) * (32 + 4) * (2));
        t1 = orig[i_col + 1] + orig[i_col + 32 + 4] + orig[i_col + (32 + 4) * 2] + orig[i_col - 1] + orig[i_col - (32 + 4)] + orig[i_col - (32 + 4) * 2] + orig[i_col];
        t2 = orig[j_col + 1] + orig[j_col + 32 + 4] + orig[j_col + (32 + 4) * 2] + orig[j_col - 1] + orig[j_col - (32 + 4)] + orig[j_col - (32 + 4) * 2] + orig[j_col];
        t3 = orig[k_col + 1] + orig[k_col + 32 + 4] + orig[k_col + (32 + 4) * 2] + orig[k_col - 1] + orig[k_col - (32 + 4)] + orig[k_col - (32 + 4) * 2] + orig[k_col];
        bound = (C0 * (t1 + t2 + t3)) + (C1 * (orig[i_col] + orig[j_col] + orig[k_col]));
        sol[i_col + (32 + 4) * (j_col + (32 + 4) * (k_col))];
      }
    }
  }
}