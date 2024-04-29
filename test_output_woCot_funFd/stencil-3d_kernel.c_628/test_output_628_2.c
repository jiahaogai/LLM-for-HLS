#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        idx = (((((k - 1) * 40) + (j - 1)) * 40) + (i - 1)) * 3;
        idx_col = (((((k - 1) * 4) + 1) * 40) + ((j - 1) * 4) + 1) * 3;
        t = ((((orig[idx + 1] + orig[idx + 4]) + orig[idx + 7]) + orig[idx + 10]) + ((orig[idx + 11] + orig[idx + 14]) + orig[idx + 17]) + orig[idx + 20]) + -(((((orig[idx] + orig[idx + 3]) + orig[idx + 6]) + orig[idx + 9]) + orig[idx + 16]) + ((orig[idx + 18] + orig[idx + 21]) + orig[idx + 24]) + orig[idx + 27]);
        sol[idx_col] = t;
        t = ((((orig[idx + 21] + orig[idx + 24]) + orig[idx + 27]) + (orig[idx + 18] + orig[idx + 21])) + ((orig[idx + 11] + orig[idx + 14]) + orig[idx + 17])) + -((((orig[idx + 7] + orig[idx + 10]) + orig[idx + 13]) + (orig[idx + 4] + orig[idx + 7])) + ((orig[idx] + orig[idx + 3]) + orig[idx + 6]));
        sol[idx_col + 1] = t;
        t = (orig[idx + 27] + orig[idx + 24] + orig[idx + 21] + orig[idx + 18] + orig[idx + 11] + orig[idx + 4] + (-1 * (orig[idx + 14] + orig[idx + 17] + orig[idx + 20] + orig[idx + 13] + orig[idx + 7] + orig[idx + 10] + orig[idx + 3] + orig[idx + 6]))) + 16;
        sol[idx_col + 2] = t;
      }
    }
  }
}