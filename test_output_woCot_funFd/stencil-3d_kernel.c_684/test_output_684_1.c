#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        i_col = i - 1 + ((j - 1) * 34) + ((k - 1) * 34 * 34);
        j_col = j - 1 + ((k - 1) * 34);
        k_col = k - 1;
        buf = C0 * (orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1 + 34 * 34] + orig[j_col + 1 + 34 * 34] + orig[k_col - 1 + 34 * 34 * 34] + orig[k_col + 1 + 34 * 34 * 34]) / 6.0;
        buf += C1 * orig[i_col];
        sol[i_col] = buf;
      }
    }
  }
}