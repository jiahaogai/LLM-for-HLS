#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32 - 1; k < 32 + 1 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 3; i++) {
        idx = i + (j + (k * 32)) * 32;
        idx_col = i_col + (j_col + (k_col * 32)) * 32;
        t = C0 * (orig[idx_col - 1] + orig[idx_col + 1]) + C1 * orig[idx_col];
        sol[idx] = t;
      }
    }
    k_col = k;
  }
  loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 32 + 1 - 3; j_col++) {...} */
  for (j_col = 1 + 32 - 1; j_col < 32 + 1 - 3; j_col++) {
    loop_i_col:
/* Standardize from: for(i_col = 1; i_col < 32 + 1 - 3; i_col++) {...} */
    for (i_col = 1 + 32 - 1; i_col < 32 + 1 - 3; i_col++) {
      idx_col = i_col + (j_col + (k_col * 32)) * 32;
      orig[idx_col] = sol[idx_col];
    }
  }
}