#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1 + 32; i > 32 + 1; i--) {
        i_row = i + -32;
        j_row = j + -32;
        k_row = k + -32;
        i_col = i - 1 + -32;
        j_col = j - 1 + -32;
        k_col = k - 1 + -32;
        idx_row = i_row * 32 + j_row * 3 + k_row;
        idx_col = i_col * 32 + j_col * 3 + k_col;
        idx = idx_row * 32 + idx_col;
        t = C0 * (orig[idx] + orig[idx + 1] + orig[idx + 32] + orig[idx + 33] + orig[idx + 364] + orig[idx + 365] + orig[idx + 368] + orig[idx + 369]);
        t += C1 * (orig[idx + 16] + orig[idx + 17] + orig[idx + 34] + orig[idx + 35] + orig[idx + 376] + orig[idx + 377] + orig[idx + 380] + orig[idx + 381]);
        sol[idx] = t;
      }
    }
  }
}