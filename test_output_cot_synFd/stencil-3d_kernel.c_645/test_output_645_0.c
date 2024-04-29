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
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        k_col = ((32 + 1) * (32 + 1)) * k;
        i_col = ((32 + 1) * i);
        j_col = ((32 + 1) * j);
        k_row = ((32 + 1) * (32 + 1)) * (32 + 1 - 1) + k_col;
        i_row = (32 + 1) * (32 + 1 - 1) + i_col;
        j_row = (32 + 1) * (32 + 1 - 2) + j_col;
        bound = (32 + 1) * (32 + 1) - 1;
        t = orig[k_col + i_col + j_col] + ((C0 * orig[k_col + bound + j_col]) + (C1 * (orig[i_col + j_col] + orig[j_col + bound])));
        sol[k_row + i_row + j_row] = t;
      }
    }
  }
}