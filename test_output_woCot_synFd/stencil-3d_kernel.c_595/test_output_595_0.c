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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = ((orig[i + (j + (k * 32L)) * 39304] + orig[i_col + (j + (k * 32L)) * 39304] + orig[i + (j_col + (k * 32L)) * 39304] + orig[i_col + (j_col + (k * 32L)) * 39304]) - (orig[i + (j + (k_col * 32L)) * 39304] + orig[i_col + (j + (k_col * 32L)) * 39304] + orig[i + (j_col + (k_col * 32L)) * 39304] + orig[i_col + (j_col + (k_col * 32L)) * 39304])) / (C0 * (long )8);
        tmp = buf;
        sol[i + (j + (k * 32L)) * 32768] = tmp;
      }
    }
  }
}