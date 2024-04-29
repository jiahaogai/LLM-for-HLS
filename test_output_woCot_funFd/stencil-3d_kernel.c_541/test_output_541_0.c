#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long _in_i;
  long _in_j;
  long _in_k;
  long _out_i;
  long _out_j;
  long _out_k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 1; k < 32 + 1 - 1; k++) {
      loop_i:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 1; i < 32 + 1 - 1; i++) {
        _in_i = 1 + 1 + i;
        _in_j = 1 + 1 + j;
        _in_k = 1 + 1 + k;
        t = 0;
        loop_t:
        for (t = 0; t < 4; t++) {
          _out_i = _in_i - 1 + ((0 > (- 1 + t)) & (- 1 + t));
          _out_j = _in_j - 1 + ((0 > (- 1 + t)) & (- 1 + t));
          _out_k = _in_k - 1 + ((0 > (- 1 + t)) & (- 1 + t));
          t = _out_i * 32 * 32 + _out_j * 32 + _out_k;
          t = orig[t];
        }
        _out_i = _in_i - 1 + 0;
        _out_j = _in_j - 1 + 0;
        _out_k = _in_k - 1 + 0;
        sol[_out_i * 32 * 32 + _out_j * 32 + _out_k] = t;
      }
    }
  }
}