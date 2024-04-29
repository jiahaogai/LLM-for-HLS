#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        i_row = i + 31L;
        j_row = j + 31L;
        k_row = k + 31L;
        sum0 = ((orig[i_row * 32L + j_row * 32L + k_row] + orig[i_row * 32L + j_row * 32L + k_col] + orig[i_row * 32L + j_col * 32L + k_row]) + (orig[i_row * 32L + j_col * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_row] + orig[i_col * 32L + j_row * 32L + k_col])) + (orig[i_col * 32L + j_col * 32L + k_row] + orig[i_col * 32L + j_col * 32L + k_col]);
        sum1 = ((orig[i_row * 32L + j_row * 32L + k_col] + orig[i_row * 32L + j_row * 32L + k_row] + orig[i_row * 32L + j_col * 32L + k_row]) + (orig[i_row * 32L + j_col * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_row])) + (orig[i_col * 32L + j_col * 32L + k_row] + orig[i_col * 32L + j_col * 32L + k_col]);
        mul0 = sum0 * 32L;
        mul1 = sum1 * 32L;
        sol[i * 32L + j * 32L + k] = ((mul0 + mul1) + 160L) >> 8;
      }
    }
  }
}