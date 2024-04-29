#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long down;
  long up;
  long left;
  long right;
  long center;
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        k_col = ((k - 2) * 34) + 2;
        i_col = ((i - 2) * 34) + 2;
        down = k_col * 34 + i_col;
        up = down - 34;
        left = down - 1;
        right = down + 1;
        center = down;
        idx = i - 2 + (j - 2) * (32 + 2) + (k - 2) * (32 + 2) * (32 + 2);
        sol[center] = ((C0 * orig[center]) + (C1 * (orig[left] + orig[right] + orig[up] + orig[down]))) / (C1 * (long )4) + ((1.0 - C0 - C1) * orig[center]);
      }
    }
  }
}