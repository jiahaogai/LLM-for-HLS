#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopk_col:
    for (k_col = 1; k_col < 392 + 1; k_col++) {
      i_col = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      while (1) {
        if (i_col > 392) {
          break;
        }
        idx_col = (((k_col - 1) * (392 + 2) + (i_col - 1)) * (392 + 2) + (j - 1)) ;
        t = (C0 * (orig[idx_col] - (orig[idx_col - 1] + orig[idx_col + 1]))) + (C1 * (orig[idx_col + (392 + 2)] - orig[idx_col])) ;
        sol[idx_col] = t;
        i_col ++;
      }
    }
    k_col --;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 392 + 1; k++) {
      i = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      loopi:
      while (1) {
        if (i > 392) {
          break;
        }
        idx = (((k - 1) * (392 + 2) + (i - 1)) * (392 + 2) + (j - 1)) ;
        t = (C0 * (sol[idx] - (sol[idx - 1] + sol[idx + 1]))) + (C1 * (sol[idx + (392 + 2)] - sol[idx])) ;
        orig[idx] = t;
        i ++;
      }
    }
  }
}