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
  long buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1; k_col < 40 + 1L; k_col++) {
    long k_col_tmp = 40L + 1L - k_col;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
    for (j_col = 1; j_col < 40 + 1L; j_col++) {
      long j_col_tmp = 40L + 1L - j_col;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1; i_col < 40 + 1L; i_col++) {
        long i_col_tmp = 40L + 1L - i_col;
        buf = 0L;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
        for (k = 1; k < 40 + 1L; k++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{8}
          loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
          for (j = 1; j < 40 + 1L; j++) {
            
#pragma ACCEL PARALLEL FACTOR=auto{8}
            loopi:
/* Standardize from: for(i = 1;i < 40;i++) {...} */
            for (i = 1; i < 40 + 1L; i++) {
              buf += orig[i + (j + (k * 40L)) * 1L] * 1L;
            }
          }
        }
        sol[i_col + (j_col_tmp + (k_col_tmp * 40L)) * 1L] = buf;
      }
    }
  }
}