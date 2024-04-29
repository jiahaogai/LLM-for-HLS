#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_row = i + 1;
        j_row = j + 1;
        k_row = k + 1;
        i_col = i + (32L * 32L);
        j_col = j + (32L * 32L);
        k_col = k + (32L * 32L);
        sum = ((orig[i_col + j_col + k_col] + orig[i_col + j_col + k - 3]) + (orig[i_col + j_col + k + 3] + orig[i_col + j_col + k_row])) + (orig[i_col + j_col + k_row - 3] + orig[i_col + j_col + k_row + 3]) + (orig[i_col + j_col + k - 3 - 3] + orig[i_col + j_col + k - 3 + 3]) + (orig[i_col + j_col + k + 3 - 3] + orig[i_col + j_col + k + 3 + 3]) + (orig[i_col + j_col + k_row - 3 - 3] + orig[i_col + j_col + k_row - 3 + 3]) + (orig[i_col + j_col + k_row + 3 - 3] + orig[i_col + j_col + k_row + 3 + 3]) + (orig[i_col + j_col + k - 3 - 3 - 3] + orig[i_col + j_col + k - 3 - 3 + 3]) + (orig[i_col + j_col + k - 3 + 3 - 3] + orig[i_col + j_col + k - 3 + 3 + 3]) + (orig[i_col + j_col + k + 3 - 3 - 3] + orig[i_col + j_col + k + 3 - 3 + 3]) + (orig[i_col + j_col + k + 3 + 3 - 3] + orig[i_col + j_col + k + 3 + 3 + 3]);
        sol[i_col + j_col + k_col] = (sum + C0) / C1;
      }
    }
  }
}