#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long tid;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 32 + 1 - 3;k_col++) {...} */
    for (k_col = 1 + 32 - 3; k_col < 32 + 1 - 1; k_col++) {
      i_col = 1 + 32 - 3 - k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopik:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 3; i < 32 + 1 - 1; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{3}
        tid = i * 32 + j;
        sol[tid] = C0 * orig[tid] + C1 * (orig[tid - 32 - 1] + orig[tid - 32] + orig[tid - 32 + 1] + orig[tid - 1] + orig[tid + 1] + orig[tid + 32 - 1] + orig[tid + 32] + orig[tid + 32 + 1]);
      }
    }
  }
}