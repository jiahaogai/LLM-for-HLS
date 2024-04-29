Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1)
{
  long i;
  long j;
  long k;
  long k_col;
  long k_row;
  long k_pls;
  long k_min;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < N - 1;j++) {...} */
  for (j = 1 + 1 ; j < 32 - 1 ; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_row:
/* Standardize from: for(k_row = 1;k_row < K;k_row++) {...} */
    for (k_row = 1 + 1 ; k_row < 16 + 1 ; k_row++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < N - 1;i++) {...} */
      for (i = 1 + 1 ; i < 32 - 1 ; i++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk_col:
/* Standardize from: for(k_col = 1;k_col < K;k_col++) {...} */
        for (k_col = 1 + 1 ; k_col < 16 + 1 ; k_col++) {
          long in = ((k_col - 1) + (j - 1) * 16) * 32 + (i - 1);
          long out = ((k_row - 1) + (k_col - 1) * 16) * 32 + (i - 1);
          sol[out] = 0.125 * (c0 * orig[in] + c1 * (orig[in - 1] + orig[in + 1] + orig[in - 32] + orig[in + 32]));
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_pls:
/* Standardize from: for(k_pls = 1;k_pls < K;k_pls++) {...} */
    for (k_pls = 1 + 1 ; k_pls < 16 + 1 ; k_pls++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_min:
/* Standardize from: for(k_min = 0;k_min < K - 1;k_min++) {...} */
      for (k_min = 0 + 1 ; k_min < 16 + 1 - 1 ; k_min++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopi_1:
/* Standardize from: for(i = 1;i < N - 1;i++) {...} */
        for (i = 1 + 1 ; i < 32 - 1 ; i++) {
          long out = (k_pls - 1) + (k_min - 1) * 16 + (i - 1) * 16 * 16;
          long in = (k_pls - 1 + 1) + (k_min - 1 + 1) * 16 + (i - 1) * 16 * 16;
          sol[out] = orig[in];
        }
      }
    }
  }
}