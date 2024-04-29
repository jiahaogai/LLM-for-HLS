#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        t1 = orig[i_col + 30L * (j_col + 30L * k_col)] - 2L * orig[i_col + 1L + 30L * (j_col + 30L * k_col)] + orig[i_col + 31L + 30L * (j_col + 30L * k_col)];
        t2 = orig[i_col + 30L * (j_col + 30L * k_col)] - orig[i_col + 31L + 30L * (j_col + 30L * k_col)];
        t3 = orig[i_col + 1L + 30L * (j_col + 30L * k_col)] - 2L * orig[i_col + 30L * (j_col + 30L * k_col)] + orig[i_col + 1L + 30L * (j_col + 30L * k_col)];
        bound = (C0 << 7) + (C1 << 1) + 1L;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopk_col:
        for (k_col = 0L; k_col < 30L; k_col++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{2}
          loopj_col:
          for (j_col = 0L; j_col < 30L; j_col++) {
            sol[i + 1L + 32L * (j + 1L + 32L * (k + 1L))] = ((t1 < bound ? t1 : bound) - 2L * (t2 < bound ? t2 : bound)) + ((t3 < bound ? t3 : bound));
          }
        }
      }
    }
  }
}