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
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i < 32 + 1; i++) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        buf = orig[idx];
        k_col = idx - 32 * 32;
        j_col = idx - 32;
        i_col = idx;
        sol[idx] = ((buf + orig[k_col + j_col + i_col - 1]) + (buf + orig[k_col + j_col + i_col + 1])) + ((buf + orig[k_col + j_col - 32 + i_col]) + (buf + orig[k_col + j_col + 32 + i_col])) + ((buf + orig[k_col - 32 + j_col + i_col]) + (buf + orig[k_col + 32 + j_col + i_col])) + (buf + orig[k_col - 32 + j_col - 1 + i_col]) + (buf + orig[k_col + 32 + j_col - 1 + i_col]) + (buf + orig[k_col - 32 + j_col + 1 + i_col]) + (buf + orig[k_col + 32 + j_col + 1 + i_col])) / 8;
      }
    }
  }
}