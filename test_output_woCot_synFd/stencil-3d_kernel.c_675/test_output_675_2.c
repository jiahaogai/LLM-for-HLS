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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 16; k_col++) {
      buf[k_col] = orig[INDEX(k_col, j, 1)];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 16; i_col++) {
        tmp = buf[k_col - 1];
        buf[k_col - 1] = buf[k_col];
        buf[k_col] = ((tmp + buf[k_col + 1]) + (buf[k_col - 16] + buf[k_col + 16])) + orig[INDEX(k_col, j, k)];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 392 + 1; i++) {
        tmp = buf[0];
        buf[0] = buf[16];
        buf[16] = tmp;
        sol[INDEX(i, j, k)] = buf[16];
      }
    }
  }
}