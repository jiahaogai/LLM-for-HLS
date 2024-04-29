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
  long buf;
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 49;j++) {...} */
  for (j = 1 + 0; j <= 49 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 49;k++) {...} */
    for (k = 1 + 0; k <= 49 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 49;i++) {...} */
      for (i = 1 + 0; i <= 49 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = orig[i_col + 49L * (j_col + 49L * k_col)] + ((tmp = orig[i_col + 49L * (j_col + 49L * (k_col - 1L))], + tmp) + orig[i_col + 49L * (j_col - 1L + 49L * k_col)] + ((tmp = orig[i_col - 1L + 49L * (j_col + 49L * k_col)], + tmp))) + orig[i_col - 1L + 49L * (j_col - 1L + 49L * k_col)];
        sol[i_col + 49L * (j_col + 49L * k_col)] = buf;
      }
    }
  }
}