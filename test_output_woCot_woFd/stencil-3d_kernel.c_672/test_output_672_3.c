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
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
  for (j = 1 + 2; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 2;k++) {...} */
    for (k = 1 + 2; k < 32 + 1 - 1; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 2;i++) {...} */
      for (i = 1 + 2; i < 32 + 1 - 1; i++) {
        i_col = i - 1 - 2;
        j_col = j - 1 - 2;
        k_col = k - 1 - 2;
        sum = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        loopbuf:
        for (long b = 0; b < 27; b++) {
          buf[b] = orig[i_col * 32 + j_col * 32 + k_col * 1 + b];
          sum += buf[b];
        }
        sol[i * 32 + j * 32 + k * 1] = sum;
      }
    }
  }
}