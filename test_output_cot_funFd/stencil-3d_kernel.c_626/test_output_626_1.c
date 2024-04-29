Code: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 33 - 1; i++) {...} */
  for (i = 1 + 0; i < 33 - 1 + 0; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 33 - 1; j++) {...} */
    for (j = 1 + 0; j < 33 - 1 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 33 - 1; k++) {...} */
      for (k = 1 + 0; k < 33 - 1 + 0; k++) {
        k_col = ((33 * (k - 1)) + 1);
        j_col = ((33 * (j - 1)) + 1);
        i_col = ((33 * (i - 1)) + 1);
        buf = (((C0 * (orig[i_col - 1] + orig[i_col + 1]))) + ((C1 * (orig[j_col - 1] + orig[j_col + 1]))) + (orig[k_col - 1]) + (orig[k_col + 1])) - (orig[i_col + j_col - 1]);
        sol[i_col + j_col + k_col - 1] = buf;
      }
    }
  }
}