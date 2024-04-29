#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[250] = {0};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        k_col = ((C0 + 2L) * k) - 32L;
        j_col = ((C1 + 2L) * j) - 32L;
        i_col = ((1L + 2L) * i) - 32L;
        buf[0] = orig[i_col + j_col + k_col];
        buf[1] = orig[i_col + j_col + k_col + 1L];
        buf[2] = orig[i_col + j_col + k_col + 1L + 1L];
        buf[3] = orig[i_col + j_col + k_col + 32L];
        buf[4] = orig[i_col + j_col + k_col + 32L + 1L];
        buf[5] = orig[i_col + j_col + k_col + 32L + 1L + 1L];
        buf[6] = orig[i_col + j_col + k_col + 32L + 32L];
        buf[7] = orig[i_col + j_col + k_col + 32L + 32L + 1L];
        buf[8] = orig[i_col + j_col + k_col + 32L + 32L + 1L + 1L];
        sol[i_col + j_col + k_col] = ((buf[0] + buf[1] + buf[2]) + (buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8])) / 32L;
      }
    }
  }
}