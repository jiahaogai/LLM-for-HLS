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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        idx = i + (j + (k * 32)) * 32;
        idx_col = i_col + (j_col + (k_col * 32)) * 32;
        t = ((((orig[idx + -1] + orig[idx + 1]) + orig[idx + 32 + -1]) + orig[idx + 32 + 1]) + orig[idx_col + -32]) + orig[idx_col + -1] + orig[idx_col + 1] + orig[idx_col + 32] + orig[idx_col + 32 + 1];
        sol[idx] = t;
      }
    }
    k_col = k;
  }
  loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 32 + 1 - 3; j_col++) {...} */
  for (j_col = 1 + 3 - 1; j_col < 32 + 1 - 3 + 1; j_col++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i_col:
/* Standardize from: for(i_col = 1; i_col < 32 + 1 - 3; i_col++) {...} */
    for (i_col = 1 + 3 - 1; i_col < 32 + 1 - 3 + 1; i_col++) {
      idx_col = i_col + (j_col + (k_col * 32)) * 32;
      sol[idx_col] = ((C0 * sol[idx_col]) + (C1 * ((orig[idx_col + -1 + -32] + orig[idx_col + 1 + -32]) + (orig[idx_col + -32] + orig[idx_col + 32]))));
    }
  }
}