#pragma ACCEL kernel

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
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1; i++) {
        i_col = i - 1 + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        j_col = j - 1 + ((k - 1) * 32);
        k_col = k - 1;
        bound = (32 * 32 * 32) - 1;
        t = 0;
        if (i_col > bound) {
          t = orig[i_col - 1] * 4;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        if (j_col > bound) {
          t += orig[j_col - 1] * 2;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        if (k_col > bound) {
          t += orig[k_col - 1];
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        if (i_col < bound) {
          t += orig[i_col + 1] * 4;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        if (j_col < bound) {
          t += orig[j_col + 1] * 2;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        if (k_col < bound) {
          t += orig[k_col + 1];
        }
        sol[i_col] = t;
      }
    }
  }
}