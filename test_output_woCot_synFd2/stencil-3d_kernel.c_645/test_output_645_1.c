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
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i > 32 + 1; i--) {
        k_col = ((32 + 1) * (32 + 1)) * k;
        i_col = ((32 + 1) * i);
        j_col = ((32 + 1) * j);
        k_row = ((32 + 1) * (32 + 1)) * (k - 1);
        i_row = ((32 + 1) * (i - 1));
        j_row = ((32 + 1) * (j - 1));
        bound = (k_col - (32 + 1)) + 1;
        t = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopbound:
        for (long _in_ = bound; _in_ > 0; _in_--) {
          t += orig[i_col + _in_] + orig[j_col + _in_] + orig[k_col + _in_] + orig[k_row + i_row + _in_] + orig[k_row + j_row + _in_] + orig[k_row + (_in_ )];
        }
        sol[j_col + i_row + k_row] = t;
      }
    }
  }
}