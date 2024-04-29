#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    long _in_k_col = 0 + 39L * (k_col - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      long _in_j_col = _in_k_col + 39L * (j_col - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        long _in_i_col = _in_j_col + i_col;
        bound = 40L * (40L - 1L) * (40L - 1L) - _in_i_col;
        t1 = 0;
        t2 = 0;
        t3 = 0;
        loopk:
/* Standardize from: for(k = 40 - 1;k > 0;k --) {...} */
        for (k = 40L - 1L; k > 0; k--) {
          long _in_k = _in_i_col + (40L - k);
          t1 = orig[_in_k] + t2;
          t2 = t1 + t3;
          t3 = t2 + orig[_in_k - 1L];
        }
        sol[_in_i_col] = t1 + t2 + t3;
      }
    }
  }
}