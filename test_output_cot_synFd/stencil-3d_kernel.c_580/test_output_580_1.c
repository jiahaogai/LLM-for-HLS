Code: #pragma ACCEL kernel

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
  for (j = 1; j < 392; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      i_col = 1 + k_col * 392;
      t = orig[i_col];
      sol[i_col] = t;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i < 392; i++) {
        idx = i + j * 392;
        idx_col = i_col + k_col * 392;
        t = ((orig[idx_col] + orig[idx - 1] + orig[idx + 1] + orig[idx - 392] + orig[idx + 392]) / 5L);
        sol[idx] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32;k++) {...} */
  for (k = 1; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 0; j_col < 392; j_col++) {
      i_col = 1 + k_col * 392;
      idx_col = i_col + j_col;
      sol[idx_col] = orig[idx_col];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      for (i = 1; i < 392; i++) {
        idx = i + j * 392;
        t = ((sol[idx_col] + sol[idx - 1] + sol[idx + 1] + sol[idx - 392] + sol[idx + 392]) / 5L);
        sol[idx] = t;
      }
    }
  }
}