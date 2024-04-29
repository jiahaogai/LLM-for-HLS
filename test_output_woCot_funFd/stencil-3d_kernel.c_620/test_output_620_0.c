#pragma ACCEL kernel

void stencil3d(long C0[32],long C1[32],long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in;
  long _out;
  long _mid;
  long _in_left;
  long _in_right;
  long _in_back;
  long _in_front;
  long _in_bottom;
  long _in_top;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32;j-- > 32 + 1;) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32;k-- > 32 + 1;) {
      _in = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      for (i = 1;i < 32 + 1 - 1;i++) {
        idx = i + 32 * (k + 32 * j);
        _out = ((C0[idx] + C1[idx]) + _in) + orig[idx];
        sol[idx] = _out;
        _in = _out;
      }
    }
  }
}