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
  long mid;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{30}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i > 32 + 1; i--) {
        mid = ((32 + 1) / 2);
        k_col = (32 + 1) - k;
        i_col = (32 + 1) - i;
        down = ((k_col * (32 + 1)) + i_col) - 1;
        up = ((k_col + 1) * (32 + 1)) - i_col - 1;
        left = (k_col - 1) * (32 + 1);
        right = (k_col + 1) * (32 + 1) - 1;
        tmp = ((((orig[down] + orig[up]) + (orig[left] + orig[right])) / 4) - orig[mid]) / C0;
        sol[mid] = tmp;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k_col:
/* Standardize from: for(k_col = 1; k_col < 32 + 1; k_col++) {...} */
    for (k_col = 1; k_col < 33; k_col++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_col:
/* Standardize from: for(i_col = 1; i_col < 32 + 1; i_col++) {...} */
      for (i_col = 1; i_col < 33; i_col++) {
        mid = ((32 + 1) / 2);
        k_col = (32 + 1) - k;
        i_col = (32 + 1) - i;
        down = ((k_col * (32 + 1)) + i_col) - 1;
        up = ((k_col + 1) * (32 + 1)) - i_col - 1;
        left = (k_col - 1) * (32 + 1);
        right = (k_col + 1) * (32 + 1) - 1;
        orig[mid] = ((((sol[down] + sol[up]) + (sol[left] + sol[right])) / 4) - sol[mid]) / C1;
      }
    }
  }
}