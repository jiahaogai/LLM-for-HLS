#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        j_col = (32L + 1L) * j;
        i_col = i;
        sum = 0L;
        loopbuf:
        for (long _in_buf = 0; _in_buf < 27L; _in_buf++) {
          buf[_in_buf] = orig[((_in_buf + i_col) - 1L) + ((j_col + _in_buf) - 1L) + (k_col - 1L)];
          sum += buf[_in_buf];
        }
        sol[i_col + j_col + k_col] = sum;
      }
    }
  }
}