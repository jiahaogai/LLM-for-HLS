#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double _in_[8];
  double _out_[8];
  double _tmp_[8];
  double tmp;
  int r;
  int q;
  int p;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 3; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (q = 0; q < 3; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 3; p++) {
        _in_[0] = orig[r * 3 * 3 + q * 3 + p];
        _in_[1] = orig[r * 3 * 3 + q * 3 + p + 1];
        _in_[2] = orig[r * 3 * 3 + q * 3 + p + 2];
        _in_[3] = orig[r * 3 * 3 + q * 3 + p + 3];
        _in_[4] = orig[r * 3 * 3 + q * 3 + p + 6];
        _in_[5] = orig[r * 3 * 3 + q * 3 + p + 7];
        _in_[6] = orig[r * 3 * 3 + q * 3 + p + 8];
        _in_[7] = orig[r * 3 * 3 + q * 3 + p + 9];
        _tmp_[0] = _in_[0] + _in_[1] + _in_[2];
        _tmp_[1] = _in_[7] + _in_[4] + _in_[1];
        _tmp_[2] = _in_[8] + _in_[5] + _in_[2];
        _tmp_[3] = _in_[6] + _in_[9] + _in_[3];
        _tmp_[4] = _in_[6] + _in_[7] + _in_[8];
        _tmp_[5] = _in_[9] + _in_[4] + _in_[5];
        _tmp_[6] = _in_[3] + _in_[1] + _in_[1];
        _tmp_[7] = _in_[4] + _in_[2] + _in_[5];
        tmp = _tmp_[0] + _tmp_[4];
        sol[r * 3 * 3 + q * 3 + p] = tmp;
        tmp = _tmp_[1] + _tmp_[3];
        sol[r * 3 * 3 + q * 3 + p + 1] = tmp;
        tmp = _tmp_[2] + _tmp_[6];
        sol[r * 3 * 3 + q * 3 + p + 2] = tmp;
        tmp = _tmp_[5] + _tmp_[7];
        sol[r * 3 * 3 + q * 3 + p + 3] = tmp;
        tmp = 0.125 * (tmp + _tmp_[4]);
        sol[r * 3 * 3 + q * 3 + p + 6] = tmp;
        tmp = 0.125 * (tmp + _tmp_[3]);
        sol[r * 3 * 3 + q * 3 + p + 7] = tmp;
        tmp = 0.125 * (tmp + _tmp_[2]);
        sol[r * 3 * 3 + q * 3 + p + 8] = tmp;
        tmp = 0.125 * (tmp + _tmp_[1]);
        sol[r * 3 * 3 + q * 3 + p + 9] = tmp;
      }
    }
  }
}