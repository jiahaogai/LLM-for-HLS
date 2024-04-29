#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[39304],double sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  double value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        i_col = i - 1 + (-1 * 32);
        j_col = j - 1 + (-1 * 32 * 32);
        k_col = k - 1 + (-1 * 32 * 32 * 32);
        value = orig[i_col + 32 * (j_col + 32 * k_col)] ;
        sol[i_col + 32 * (j_col + 32 * k_col)] = (1.0 / 12.0) * (value + 2.0 * (value = orig[i_col + 1 + 32 * (j_col + 32 * k_col)]) + value + 2.0 * (value = orig[i_col - 1 + 32 * (j_col + 32 * k_col)]) + value + 2.0 * (value = orig[i_col + 32 * (j_col + 1 + 32 * k_col)]) + value + 2.0 * (value = orig[i_col + 32 * (j_col - 1 + 32 * k_col)]) + value + 2.0 * (value = orig[i_col + 32 * (j_col + 32 * (k_col - 1))]) + value + 2.0 * (value = orig[i_col + 32 * (j_col + 32 * (k_col + 1))]));
      }
    }
  }
}