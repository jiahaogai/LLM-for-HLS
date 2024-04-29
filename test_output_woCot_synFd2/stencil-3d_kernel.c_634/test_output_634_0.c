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
  long buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        k_col = ((32L + 1L) - 3L) - k;
        j_col = ((32L + 1L) - 3L) - j;
        i_col = ((32L + 1L) - 3L) - i;
        buf = (C0 * (orig[i + (j + (k * 32L)) * 39304] + orig[i_col + (j + (k * 32L)) * 39304])) + (C1 * (orig[i + (j_col + (k * 32L)) * 39304] + orig[i_col + (j_col + (k * 32L)) * 39304]));
        sol[i + (j + (k * 32L)) * 32768] = buf;
      }
    }
  }
}