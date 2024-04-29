- `long C0`: Constant used in the stencil computation.
- `long C1`: Constant used in the stencil computation.
- `long orig[39304]`: Array of original data.
- `long sol[32768]`: Array in which to store the result of the stencil computation.
- `long i;`: Loop variable for the outer loop.
- `long j;`: Loop variable for the middle loop.
- `long k;`: Loop variable for the inner loop.
- `long idx;`: Array index.
- `long t;`: Temporary variable.
- `C0`: Index into the `orig` array.
- `C1`: Index into the `orig` array.
- `-1`: Index into the `orig` array.
- `1`: Index into the `orig` array.
- `orig[C0]`: Value in the `orig` array.
- `orig[C1]`: Value in the `orig` array.
- `orig[C1 - 1]`: Value in the `orig` array.
- `orig[C1 + 1]`: Value in the `orig` array.
- `orig[C0 - 1]`: Value in the `orig` array.
- `orig[C0 + 1]`: Value in the `orig` array.
- `orig[C1 - 2]`: Value in the `orig` array.
- `orig[C1 - 1]`: Value in the `orig` array.
- `orig[C1]`: Value in the `orig` array.
- `orig[C1 + 1]`: Value in the `orig` array.
- `orig[C1 + 2]`: Value in the `orig` array.
- `orig[C0 - 2]`: Value in the `orig` array.
- `orig[C0 - 1]`: Value in the `orig` array.
- `orig[C0]`: Value in the `orig` array.
- `orig[C0 + 1]`: Value in the `orig` array.
- `orig[C0 + 2]`: Value in the `orig` array.
- `t = 0`: Initial value for `t`.
- `t = C0 * C1 * orig[i] + C1 * orig[i + 1] + orig[i + 2]`: Aggregate value for `t`.
- `sol[idx] = t`: Index into the `sol` array.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1 - 1; k++) {
      loopi:
/* Standardize from: for(i = 1;i < 390 + 1 - 3;i++) {...} */
      for (i = 1 + 390 - 1; i < 390 + 1 - 3; i++) {
        idx = i + 390 * (k + 32 * j);
        t = C0 * (C1 * orig[idx] + orig[idx + 1]) + orig[idx + 2];
        sol[idx] = t;
      }
    }
  }
}