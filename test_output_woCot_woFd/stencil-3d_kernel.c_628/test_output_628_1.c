#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[8];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
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
        sum = 0L;
        buf[0] = orig[i_col + 32L * (j_col + 32L * k_col)];
        buf[1] = orig[i_col + 1L + 32L * (j_col + 32L * k_col)];
        buf[2] = orig[i_col - 1L + 32L * (j_col + 32L * k_col)];
        buf[3] = orig[i_col + 32L * (j_col + 1L + 32L * k_col)];
        buf[4] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[5] = orig[i_col - 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[6] = orig[i_col + 32L * (j_col - 1L + 32L * k_col)];
        buf[7] = orig[i_col + 1L + 32L * (j_col - 1L + 32L * k_col)];
        buf[8] = orig[i_col - 1L + 32L * (j_col - 1L + 32L * k_col)];
        
#pragma ACCEL PARALLEL FACTOR=auto{3}
        loopk_col:
        for (long k_col = 0; k_col < 1L; k_col++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{2}
          loopj_col:
          for (long j_col = 0; j_col < 1L; j_col++) {
            
#pragma ACCEL PARALLEL FACTOR=auto{1}
            loopi_col:
            for (long i_col = 0; i_col < 1L; i_col++) {
              sum += buf[k_col + 2L * (j_col + 2L * i_col)];
            }
          }
        }
        sol[i + 32L * (j + 32L * k)] = sum;
      }
    }
  }
}