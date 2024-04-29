Code: #pragma ACCEL kernel

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
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        tmp = 0;
        loopbuf:
/* Standardize from: for(int buf = 0; buf < 256; buf++) {...} */
        for (long buf = 0; buf < 256 + 0; buf++) {
          tmp += orig[i_col * 392 + j_col] * buf;
          i_col = i_col + 1;
        }
        buf[k_col] = tmp;
        k_col = k_col + 1;
      }
/* Standardize from: for(k = 1;k < 32;k++) {...} */
      loopk_1:
      for (k = 1; k < 32 + 0; k++) {
        tmp = 0;
        loopbuf_1:
/* Standardize from: for(int buf = 0; buf < 256; buf++) {...} */
        for (long buf = 0; buf < 256 + 0; buf++) {
          tmp += buf[k_col] * k;
          k_col = k_col + 1;
        }
        sol[i * 32 + k] = tmp;
      }
    }
  }
}