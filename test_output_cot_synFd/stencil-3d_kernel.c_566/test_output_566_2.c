#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long bound;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        i_row = i - 1L;
        j_row = j - 1L;
        k_row = k - 1L;
        i_col = i + 30L;
        j_col = j + 30L;
        k_col = k + 30L;
        bound = (32L * 32L) * (32L - 1L);
        sum0 = orig[i_col * (32L * 32L) + j_col * (32L) + k_col] + orig[i_col * (32L * 32L) + j_col * (32L) + k_row] + orig[i_col * (32L * 32L) + j_row * (32L) + k_col] + orig[i_col * (32L * 32L) + j_row * (32L) + k_row] + orig[i_row * (32L * 32L) + j_col * (32L) + k_col] + orig[i_row * (32L * 32L) + j_col * (32L) + k_row] + orig[i_row * (32L * 32L) + j_row * (32L) + k_col] + orig[i_row * (32L * 32L) + j_row * (32L) + k_row];
        sum1 = sum0;
        mul0 = sum0 * 2L;
        mul1 = sum1 * 2L;
        sol[i * (32L) + j + (32L * (32L - 1L)) * k] = (mul0 + mul1 + ((bound + 4L) % (32L * 32L * 32L))) % ((32L * 32L * 32L) - 1L);
      }
    }
  }
}