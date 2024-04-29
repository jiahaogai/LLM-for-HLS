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
  loopj:
/* Standardize from: for(j = 1;j < 408;j++) {...} */
  for (j = 1 + 0; j <= 408 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 408;k_col++) {...} */
    for (k_col = 1 + 0; k_col <= 408 - 1 + 0; k_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
      for (i_col = 1 + 0; i_col <= 408 - 1 + 0; i_col++) {
        buf += C0 * (orig[i_col + 408L * (j_col = j + -1 + 0)] + orig[i_col + 408L * (j_col + 1)]);
      }
      sol[k_col + 408L * k] = buf;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 408;k++) {...} */
    for (k = 1 + 0; k <= 408 - 1 + 0; k++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1 + 0; i <= 408 - 1 + 0; i++) {
        buf += C1 * (sol[i + 408L * (k_col = k + -1 + 0)] + sol[i + 408L * (k_col + 1)]);
      }
      sol[i + 408L * k] = buf;
    }
  }
}