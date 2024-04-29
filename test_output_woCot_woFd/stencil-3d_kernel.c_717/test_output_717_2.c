- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute loop iterations of the middle loop concurrently in batches of 2 for parallelism.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the outer loop concurrently in batches of 1 for parallelism.
- `long C0`: Constant used in the stencil computation.
- `long C1`: Constant used in the stencil computation.
- `long orig[39304]`: Array of original data.
- `long sol[32768]`: Array in which to store the result of the stencil computation.
- `long i`: Loop counter for the `orig` array.
- `long j`: Loop counter for the `orig` array.
- `long k`: Loop counter for the `orig` array.
- `long idx`: Array index.
- `long idxm1`: Array index.
- `long idxp1`: Array index.
- `long idxm32`: Array index.
- `long idxp32`: Array index.
- `long idxm132`: Array index.
- `long idxp132`: Array index.
- `long tmp`: Temporary variable.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long idxm1;
  long idxp1;
  long idxm32;
  long idxp32;
  long idxm132;
  long idxp132;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392; k++) {
      idx = i * 392 + j * 392 + k;
      idxm1 = idx - 1;
      idxp1 = idx + 1;
      idxm32 = idx - 392;
      idxp32 = idx + 392;
      idxm132 = idxm1 - 392;
      idxp132 = idxp1 - 392;
      tmp = C0 * (orig[idxm132] + orig[idxp132]) + C1 * (orig[idxm32] + orig[idxp32]) - orig[idx];
      sol[idx] = tmp;
/* Standardize from: for(k = 1;k < 392;k++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopkp1:
      for (k = 1; k < 392; k++) {
        idx = i * 392 + j * 392 + k;
        idxm1 = idx - 1;
        idxp1 = idx + 1;
        idxm32 = idx - 392;
        idxp32 = idx + 392;
        idxm132 = idxm1 - 392;
        idxp132 = idxp1 - 392;
        tmp = C0 * (sol[idxm132] + sol[idxp132]) + C1 * (sol[idxm32] + sol[idxp32]) - sol[idx];
        sol[idx] = tmp;
      }
/* Standardize from: for(j = 1;j < 392;j++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopjp1:
      for (j = 1; j < 392; j++) {
        idx = i * 392 + j * 392 + k;
        idxm1 = idx - 1;
        idxp1 = idx + 1;
        idxm32 = idx - 392;
        idxp32 = idx + 392;
        idxm132 = idxm1 - 392;
        idxp132 = idxp1 - 392;
        tmp = C0 * (sol[idxm132] + sol[idxp132]) + C1 * (sol[idxm32] + sol[idxp32]) - sol[idx];
        sol[idx] = tmp;
      }
    }
/* Standardize from: for(i = 1;i < 392;i++) {...} */
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopip1:
    for (i = 1; i < 392; i++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopjk:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
      for (j = 1; j < 392; j++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopkp1:
        for (k = 1; k < 392; k++) {
          idx = i * 392 + j * 392 + k;
          idxm1 = idx - 1;
          idxp1 = idx + 1;
          idxm32 = idx - 392;
          idxp32 = idx + 392;
          idxm132 = idxm1 - 392;
          idxp132 = idxp1 - 392;
          tmp = C0 * (sol[idxm132] + sol[idxp132]) + C1 * (sol[idxm32] + sol[idxp32]) - sol[idx];
          sol[idx] = tmp;
        }
/* Standardize from: for(j = 1;j < 392;j++) {...} */
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        loopjp1:
        for (j = 1; j < 392; j++) {
          idx = i * 392 + j * 392 + k;
          idxm1 = idx - 1;
          idxp1 = idx + 1;
          idxm32 = idx - 392;
          idxp32 = idx + 392;
          idxm132 = idxm1 - 392;
          idxp132 = idxp1 - 392;
          tmp = C0 * (sol[idxm132] + sol[idxp132]) + C1 * (sol[idxm32] + sol[idxp32]) - sol[idx];
          sol[idx] = tmp;
        }
      }
    }
  }
}