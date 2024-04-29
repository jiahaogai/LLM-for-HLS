#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40L * 1L * (k - 1L);
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40L * k_col;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40L * j_col;
        t1 = C0 * (orig[i_col - 1] + orig[i_col + 1] + orig[i_col + 40] + orig[i_col + 41] + orig[i_col + 160] + orig[i_col + 161] + orig[i_col + 256] + orig[i_col + 257] + orig[i_col + 320] + orig[i_col + 321] ) + C1 * orig[i_col];
        t2 = C0 * (orig[i_col - 40] + orig[i_col + 40] + orig[i_col + 160] + orig[i_col + 161] + orig[i_col + 256] + orig[i_col + 257] + orig[i_col + 320] + orig[i_col + 321] ) + C1 * orig[i_col];
        t3 = C0 * (orig[i_col - 160] + orig[i_col + 160] + orig[i_col + 256] + orig[i_col + 257] ) + C1 * orig[i_col];
        bound = (40L << 2) + 4L;
        loopbound:
/* Standardize from: for(bound = 40<<2 + 4; bound--; ) {...} */
        for (bound = ((40L << 2) + 4L) + 0; bound >= ((40L << 2) + 4L) + 0; bound--) {
          sol[i_col + bound] = t1;
        }
        sol[i_col] = t2;
        t1 = t3;
      }
    }
  }
}