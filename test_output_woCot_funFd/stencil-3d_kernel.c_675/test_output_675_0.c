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
  loopj:
/* Standardize from: for(j = 1;j < 49;j++) {...} */
  for (j = 1 + 0; j <= 49 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 49;k++) {...} */
    for (k = 1 + 0; k <= 49 - 1 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 49;i++) {...} */
      for (i = 1 + 0; i <= 49 - 1 + 0; i++) {
        i_col = i - 1 + ((49 - 1 + 0) * (k - 1 + 0));
        j_col = j - 1 + ((49 - 1 + 0) * (k - 1 + 0));
        k_col = k - 1 + ((49 - 1 + 0) * (j - 1 + 0));
        buf = orig[i_col] + orig[j_col] + orig[k_col];
        sol[i_col] = buf;
      }
    }
  }
}