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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 1 + 32 - 1; k_col < 32 + 1 - 1; k_col++) {
      i_col = 1 + 32 - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      while (i_col <= 32 + 1 - 1) {
        idx = ((32 + 1) * (32 + 1) * k_col) + ((32 + 1) * i_col) + j;
        tmp = 0.125 * (orig[idx + 32 + 1] + orig[idx + 32 - 1] + orig[idx + 1] + orig[idx - 1]);
        sol[idx] = tmp;
        i_col ++;
      }
    }
    k_col = 32 + 1 - 3;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 32 + 1 - 3; k <= 32 + 1 - 1; k++) {
      i_col = 1 + 32 - 3;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi2:
      while (i_col <= 32 + 1 - 1) {
        idx = ((32 + 1) * (32 + 1) * k) + ((32 + 1) * i_col) + j;
        tmp = 0.125 * (orig[idx + 32 + 1] + orig[idx + 32 - 1] + orig[idx + 1] + orig[idx - 1] - C0 * sol[idx]);
        sol[idx] = tmp;
        i_col ++;
      }
    }
    k = 1 + 32 - 3;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk2:
    for ( ; k <= 32 + 1 - 1 - 3; k++) {
      i_col = 1 + 32 - 3;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi3:
      while (i_col <= 32 + 1 - 1 - 3) {
        idx = ((32 + 1) * (32 + 1) * k) + ((32 + 1) * i_col) + j;
        tmp = 0.125 * (orig[idx + 32 + 1] + orig[idx + 32 - 1] + orig[idx + 1] + orig[idx - 1] - C0 * sol[idx]);
        tmp += 0.125 * (sol[idx + 32 + 1] + sol[idx + 32 - 1] + sol[idx + 1] + sol[idx - 1] - C1 * sol[idx]);
        sol[idx] = tmp;
        i_col ++;
      }
    }
  }
}