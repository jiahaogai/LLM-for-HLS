#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        sum = ((orig[i_col + 392 * (j_col + 392 * k_col)] + orig[i_col + 392 * (j_col + 392 * (k_col - 1))]) + orig[i_col + 392 * (j_col - 1 + 392 * k_col)]) + orig[i_col + 392 * (j_col - 1 + 392 * (k_col - 1))];
        sum += orig[i_col + 392 * (j_col + 392 * (k_col + 1))] + orig[i_col + 392 * (j_col + 392 * (k_col - 1 + 2))] + orig[i_col + 392 * (j_col - 1 + 392 * (k_col + 1))] + orig[i_col + 392 * (j_col - 1 + 392 * (k_col - 1 + 2))];
        sum += orig[i_col - 1 + 392 * (j_col + 392 * k_col)] + orig[i_col - 1 + 392 * (j_col + 392 * (k_col - 1))] + orig[i_col - 1 + 392 * (j_col - 1 + 392 * k_col)] + orig[i_col - 1 + 392 * (j_col - 1 + 392 * (k_col - 1))];
        sum += orig[i_col - 1 + 392 * (j_col + 392 * (k_col + 1))];
        sol[i_col + 392 * (j_col + 392 * k_col)] = (sum + C0) / C1;
      }
    }
  }
}