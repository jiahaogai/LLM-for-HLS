#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long kj;
  long ki;
  long idx;
  long idx_col;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1 + 0; i < 33 - 1; i += 1) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1 + 0; j < 33 - 1; j += 1) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1 + 0; k < 33 - 1; k += 1) {
        sum = ((C0 * (orig[i + 1 + (j + 0 + (k + 0)) * 33] + orig[i + 0 + (j + 0 + (k + 0)) * 33])) + (C1 * (orig[i + 1 + (j - 1 + (k + 0)) * 33] + orig[i + 0 + (j - 1 + (k + 0)) * 33] + orig[i + 1 + (j + 1 + (k + 0)) * 33] + orig[i + 0 + (j + 1 + (k + 0)) * 33] + orig[i + 1 + (j - 1 + (k + 1)) * 33] + orig[i + 0 + (j - 1 + (k + 1)) * 33] + orig[i + 1 + (j + 1 + (k + 1)) * 33] + orig[i + 0 + (j + 1 + (k + 1)) * 33]))) / ((32 - 2) * (32 - 2) * (32 - 2));
        idx = i + (j + (k * 33));
        sol[idx] = sum;
      }
    }
  }
}