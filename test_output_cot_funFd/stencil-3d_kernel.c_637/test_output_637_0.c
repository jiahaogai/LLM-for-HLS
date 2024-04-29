#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 4;j++) {...} */
  for (j = 1 + 0; j <= 4 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 4;k++) {...} */
    for (k = 1 + 0; k <= 4 - 1 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 4;i++) {...} */
      for (i = 1 + 0; i <= 4 - 1 + 0; i++) {
        i_col = i - 1 + ((j - 1) * 4) + ((k - 1) * 4 * 4);
        j_col = j - 1 + ((k - 1) * 4);
        k_col = k - 1;
        t = ((((orig[i_col + 4] + orig[i_col + 3]) + orig[i_col + 1]) + orig[i_col]) + ((orig[i_col + 4 + 4] + orig[i_col + 3 + 4]) + orig[i_col + 1 + 4]) + orig[i_col + 4 + 4]) - ((((orig[i_col - 1] + orig[i_col + 5]) + orig[i_col + 1]) + orig[i_col + 4]) + ((orig[i_col - 1 + 4] + orig[i_col + 5 + 4]) + orig[i_col + 1 + 4]) + orig[i_col + 4 - 1]);
        sol[i_col] = t;
      }
    }
  }
}