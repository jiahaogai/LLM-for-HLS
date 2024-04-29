#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 1 + 32 - 1; k_col < 32 + 1; k_col++) {
      i_col = 1 + 32 - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi_col:
      while (i_col <= 32 + 1 - 3) {
        idx = ((k_col - 1) * (32 + 4) + (i_col - 1)) * (34 - 1);
        tmp = C0 * (orig[idx + 34 - 1] + orig[idx + 34] + orig[idx + 34 + 1]) + C1 * (orig[idx + 32 - 1] + orig[idx + 32] + orig[idx + 32 + 1] + orig[idx + 33 - 1] + orig[idx + 33] + orig[idx + 33 + 1]);
        sol[idx + 32] = tmp;
        i_col ++;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 3; k < 34 + 1 - 3; k++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 3; i < 34 + 1 - 3; i++) {
        idx = (k * (32 + 4) + i) * (34 - 1);
        tmp = C0 * (sol[idx + 34 - 1] + sol[idx + 34] + sol[idx + 34 + 1]) + C1 * (sol[idx + 32 - 1] + sol[idx + 32] + sol[idx + 32 + 1] + sol[idx + 33 - 1] + sol[idx + 33] + sol[idx + 33 + 1]);
        sol[idx + 32] = tmp;
      }
    }
  }
}