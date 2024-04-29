#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long _in_j;
  long _in_i;
  long _in_k;
  long _out_j;
  long _out_i;
  long _out_k;
  long _in_idx;
  long _out_idx;
  long _boundary_tmp;
  long _boundary_reg;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 49;j_col++) {...} */
  for (j_col = 1; j_col <= 48; j_col++) {
    _in_j = 48;
    _out_j = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi_col:
/* Standardize from: for(i_col = 1;i_col < 49;i_col++) {...} */
    for (i_col = 1; i_col <= 48; i_col++) {
      _in_i = 48;
      _out_i = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_col:
/* Standardize from: for(k_col = 1;k_col < 49;k_col++) {...} */
      for (k_col = 1; k_col <= 48; k_col++) {
        _in_k = 48;
        _out_k = 0;
        _in_idx = ((48 + 2) * (48 + 2) * (48 + 2) - 1) + ((48 + 2) * (48 + 2) * (k_col - 1)) + ((48 + 2) * (i_col - 1)) + (i_col - 1);
        _out_idx = ((48 - 2) * (48 - 2) * (48 - 2) - 1) + ((48 - 2) * (48 - 2) * (k_col - 1)) + ((48 - 2) * (i_col - 1)) + (i_col - 1);
        buf[0] = orig[_in_idx];
        buf[1] = orig[_in_idx + 1];
        buf[2] = orig[_in_idx + 48];
        buf[3] = orig[_in_idx + 49];
        buf[4] = orig[_in_idx + 48 + 1];
        buf[5] = orig[_in_idx + 49 + 1];
        buf[6] = orig[_in_idx + 48 + 48];
        buf[7] = orig[_in_idx + 49 + 48];
        buf[8] = orig[_in_idx + 48 + 49];
        buf[9] = orig[_in_idx + 49 + 49];
        _boundary_tmp = 0;
        _boundary_reg = _boundary_tmp;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk:
/* Standardize from: for(k = 0;k < 49;k++) {...} */
        for (k = 1; k <= 48; k++) {
          _out_k += 1;
          _in_k -= 1;
          _in_idx = _in_k;
          buf[16] = orig[_in_idx];
          buf[17] = orig[_in_idx + 1];
          buf[18] = orig[_in_idx + 48];
          buf[19] = orig[_in_idx + 49];
          buf[20] = orig[_in_idx + 48 + 1];
          buf[21] = orig[_in_idx + 49 + 1];
          buf[22] = orig[_in_idx + 48 + 48];
          buf[23] = orig[_in_idx + 49 + 48];
          buf[24] = orig[_in_idx + 48 + 49];
          buf[25] = orig[_in_idx + 49 + 49];
          _boundary_tmp = 0;
          if (k == 1) {
            _boundary_tmp = 1;
          }
          if (k == 48) {
            _boundary_tmp = 2;
          }
          _boundary_reg = _boundary_tmp;
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loopj:
/* Standardize from: for(j = 0;j < 49;j++) {...} */
          for (j = 1; j <= 48; j++) {
            _out_j += 1;
            _in_j -= 1;
            _in_idx = _in_k + _in_j;
            sol[_out_idx] = (buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9]) / 32 - _boundary_reg;
            _out_idx += 1;
            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = buf[3];
            buf[3] = buf[4];
            buf[4] = buf[5];
            buf[5] = buf[6];
            buf[6] = buf[7];
            buf[7] = buf[8];
            buf[8] = buf[9];
            buf[9] = orig[_in_idx + 49];
          }
          _out_j = ((48 - 2) * 48) + ((48 - 2) * 2) - 2;
          _out_idx = _out_idx + 49 - 1;
        }
        _out_k = ((48 - 2) * 48 * 48) - 1;
        _out_idx = _out_idx + 49 * 48 * 2 - 1;
      }
    }
  }
}