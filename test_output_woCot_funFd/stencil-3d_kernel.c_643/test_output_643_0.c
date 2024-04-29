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
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40L * 1L * 1L;
     j_col = 1L * 1L;
     i_col = 1L;
     buf = orig[i_col + j_col + k_col];
     s = 0L;
     
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
      for (j = 1 + 0; j < 40 + 0; j++) {
         j_col = 40L * 1L * (j + 0L);
         i_col = 1L * (j + 0L);
         s += orig[i_col + j_col + k_col] + buf;
         buf = orig[i_col + j_col + k_col];
      }
      s = 1L + s;
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
         i_col = 1L * (i + 0L);
         j_col = 40L * 1L * 1L;
         k_col = 40L * 1L * (k + 0L);
         sol[i_col + j_col + k_col] = s;
      }
    }
}