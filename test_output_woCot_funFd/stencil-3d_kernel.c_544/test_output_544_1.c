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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j < 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 8; i_col++) {
        buf += orig[i_col + 1 + ((j_col = (k_col << 3) + k) * 392)];
      }
      sol[k_col + ((j_col << 3) + j)] = buf;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32;k++) {...} */
  for (k = 1 + 0; k < 32 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 0; j_col < 8; j_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 8; i++) {
        buf += sol[i + ((j << 3) + (k_col = (j_col << 3) + k)) * 8];
      }
      sol[i_col + ((j_col << 3) + k)] = buf;
    }
  }
}