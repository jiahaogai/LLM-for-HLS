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
  long tmp;
  long tmp_row;
  long tmp_col;
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        idx = (((((k - 1) * (32L + 1L) + (j - 1))) * (32L + 1L) + (i - 1)) * 2L);
        tmp_col = ((((k - 1) * (32L + 1L) + (j - 1))) * (32L + 1L) + (i - 1));
        tmp_row = (((k - 1) * (32L + 1L) + (j - 1)));
        buf = orig[idx + 0L] + ((orig[idx + 32L] + orig[idx + 1L]) + orig[idx - 1L]);
        tmp = orig[idx + 32L] + ((buf + orig[idx + 1L]) + orig[idx - 32L]);
        sol[tmp_col] = tmp;
        sol[tmp_row] = buf;
      }
    }
  }
}