#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     bound = (32L * 32L) * (k - 1L) + 1L;
     i_col = bound;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = i_col - 32L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i > 0L; i--) {
        sum = ((orig[i_col - 1L] + orig[i_col + 1L]) + (orig[j_col - 1L] + orig[j_col + 1L])) + (orig[k_col - 1L] + orig[k_col + 1L]);
        sol[idx] = sum;
        i_col++;
        idx++;
      }
      j_col++;
    }
    k_col++;
  }
}