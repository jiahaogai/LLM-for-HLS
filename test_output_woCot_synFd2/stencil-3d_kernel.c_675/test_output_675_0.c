#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40L * 1L * k;
     bound = 40L * (k + 1L) * 1L;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40L * j;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40L * i;
        t = orig[i_col + j_col + k_col] + ((+1L) * (orig[i_col + j_col + bound] + orig[i_col + bound + k_col] + orig[i_col + bound + bound] + orig[bound + j_col + k_col] + orig[bound + j_col + bound] + orig[bound + bound + k_col] + orig[bound + bound + bound])) / 8L;
        sol[i_col + j_col + k_col] = t;
      }
    }
  }
}