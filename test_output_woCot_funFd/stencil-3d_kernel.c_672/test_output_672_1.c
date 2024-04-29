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
  long s;
  s = 1;
  buf = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk_col:
  for (k_col = 0; k_col < 4; k_col++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 0; j_col < 4; j_col++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 4; i_col++) {
        buf = orig[s + 0];
        s++;
        buf += orig[s + 0];
        s++;
        buf += orig[s + 0];
        s++;
        buf += orig[s + 0];
        s++;
        sol[k_col + 0 + ((j_col + 0) + ((i_col + 0) * 4)) * 4] = buf / 4;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
  for (k = 1; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32; i++) {
        buf = sol[k + 0 + ((j + 0) + ((i + 0) * 4)) * 4];
        buf += sol[k - 1 + ((j + 0) + ((i + 0) * 4)) * 4];
        buf += sol[k + 1 + ((j + 0) + ((i + 0) * 4)) * 4];
        buf += sol[k + 0 + ((j - 1) + ((i + 0) * 4)) * 4];
        buf += sol[k + 0 + ((j + 1) + ((i + 0) * 4)) * 4];
        buf += sol[k + 0 + ((j + 0) + ((i - 1) * 4)) * 4];
        buf += sol[k + 0 + ((j + 0) + ((i + 1) * 4)) * 4];
        sol[k + ((j + 0) + (i * 4)) * 4] = buf / 8;
      }
    }
  }
}