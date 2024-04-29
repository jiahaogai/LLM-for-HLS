#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    long _in_k_col = 0 + 39L * (k_col - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      long _in_j_col = _in_k_col + 39L * (j_col - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        long _in_i_col = _in_j_col + i_col;
        bound = 40L * (40L - 1L) * (40L - 1L) - _in_i_col;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk:
/* Standardize from: for(k = 39;k > 0;k --) {...} */
        for (k = 39; k > 0; k--) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loopj:
/* Standardize from: for(j = 39;j > 0;j --) {...} */
          for (j = 39; j > 0; j--) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            loopi:
/* Standardize from: for(i = 39;i > 0;i --) {...} */
            for (i = 39; i > 0; i--) {
              t1 = orig[_in_i_col + 1] + orig[_in_i_col - 1] - 2L * orig[_in_i_col];
              t2 = orig[_in_i_col + 39] + orig[_in_i_col - 39] - 2L * orig[_in_i_col];
              t3 = orig[_in_i_col + 39L * 40] + orig[_in_i_col - 39L * 40] - 2L * orig[_in_i_col];
              sol[_in_i_col] = orig[_in_i_col] + C0 * (t1 + t2 + t3);
              _in_i_col--;
            }
            _in_i_col = _in_i_col + 40L - 1L;
          }
          _in_j_col = _in_j_col - 39L * 40L;
        }
        _in_k_col = _in_k_col - 39L * 40L * 40L;
      }
    }
    _in_k_col = 1L + 39L * 40L * (k_col - 1L);
  }
}