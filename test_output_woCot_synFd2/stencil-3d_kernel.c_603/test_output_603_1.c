#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 128; k_col++) {
      buf[k_col] = orig[k_col + 128 * (j - 1)];
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 128; i_col++) {
        sol[i_col + 128 * (k + 32 * (j - 1))] = ((buf[i_col - 1]) + (buf[i_col + 128]) + (buf[i_col + 128 * 2])) / C0;
      }
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 392 + 1; i++) {
        k_col = 128 * (k - 1);
        j_col = i_col = 128 * (i - 1) + k_col;
        sol[i_col] = ((buf[j_col - 128]) + (buf[j_col]) + (buf[j_col + 128]) + (buf[j_col + 128 + k_col]) + (buf[j_col + 128 - 128]) ) / C1;
      }
      for (i_col = 0; i_col < 128; i_col++) {
        buf[i_col] = sol[i_col + k_col];
      }
    }
  }
}