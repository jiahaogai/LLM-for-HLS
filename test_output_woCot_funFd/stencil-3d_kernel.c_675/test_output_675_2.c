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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    long _in_k_col = 0 + 39L * (k_col - 1);
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      long _in_j_col = _in_k_col + 38L * (j_col - 1);
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        long _in_i_col = _in_j_col + i_col - 1;
        bound = 0;
        loopk:
/* Standardize from: for(k = 1;k < 40;k ++) {...} */
        for (k = 1; k < 40; k++) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loopj:
/* Standardize from: for(j = 1;j < 40;j ++) {...} */
          for (j = 1; j < 40; j++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            loopi:
/* Standardize from: for(i = 1;i < 40;i ++) {...} */
            for (i = 1; i < 40; i++) {
              if ((((i > 0) && (i < 39)) && (j > 0)) && (j < 39)) {
                if ((((i > 0) && (i < 39)) && (k > 0)) && (k < 39)) {
                  t = ((((i - 1) + ((j - 1) * 40)) + ((k - 1) * 1600)) - _in_i_col);
                }
                
#pragma ACCEL PARALLEL FACTOR=auto{8}
                stencil:
                for ( ; t < ((3200 - _in_i_col) + 1); t++) {
                  orig[t] += + 1.0;
                }
              }
            }
          }
          k--;
          bound = 40;
        }
        j_col--;
        bound = 1600;
      }
      k_col--;
      bound = 3200;
    }
  }
}