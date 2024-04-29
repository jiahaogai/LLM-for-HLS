#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double _in_[8];
  double _out_[8];
  double _tmp_ = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (long c = 0; c < 3; c++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (long b = 0; b < 3; b++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (long a = 0; a < 3; a++) {
        _in_[0] = orig[a + 1 + (b + 1) * 3 + (c + 1) * 3 * 3];
        _in_[1] = orig[a + 1 + (b + 2) * 3 + (c + 1) * 3 * 3];
        _in_[2] = orig[a + 1 + (b + 3) * 3 + (c + 1) * 3 * 3];
        _in_[3] = orig[a + 2 + (b + 1) * 3 + (c + 1) * 3 * 3];
        _in_[4] = orig[a + 2 + (b + 2) * 3 + (c + 1) * 3 * 3];
        _in_[5] = orig[a + 2 + (b + 3) * 3 + (c + 1) * 3 * 3];
        _in_[6] = orig[a + 3 + (b + 1) * 3 + (c + 1) * 3 * 3];
        _in_[7] = orig[a + 3 + (b + 2) * 3 + (c + 1) * 3 * 3];
        _out_[0] = 0.125 * (_in_[0] + _in_[1] + _in_[2] - _in_[3] - _in_[4] - _in_[5] + _in_[6] + _in_[7]);
        _out_[1] = 0.125 * (_in_[1] + _in_[2] + _in_[5] + _in_[8] - _in_[3] - _in_[4] - _in_[7] + _in_[6]);
        _out_[2] = 0.125 * (_in_[2] + _in_[5] + _in_[8] + _in_[9] - _in_[1] - _in_[4] - _in_[7] + _in_[6]);
        _out_[3] = 0.125 * (_in_[3] + _in_[4] + _in_[7] + _in_[10] - _in_[0] - _in_[1] - _in_[6] + _in_[5]);
        _out_[4] = 0.125 * (_in_[4] + _in_[7] + _in_[10] + _in_[11] - _in_[0] - _in_[2] - _in_[6] + _in_[5]);
        _out_[5] = 0.125 * (_in_[5] + _in_[8] + _in_[11] + _in_[12] - _in_[1] - _in_[2] - _in_[7] + _in_[6]);
        _out_[6] = 0.125 * (_in_[6] + _in_[9] + _in_[12] + _in_[13] - _in_[2] - _in_[3] - _in_[7] + _in_[8]);
        _out_[7] = 0.125 * (_in_[7] + _in_[10] + _in_[13] + _in_[14] - _in_[3] - _in_[4] - _in_[8] + _in_[9]);
        sol[a + 1 + (b + 1) * 3 + (c + 1) * 3 * 3] = _out_[0];
        sol[a + 1 + (b + 2) * 3 + (c + 1) * 3 * 3] = _out_[1];
        sol[a + 1 + (b + 3) * 3 + (c + 1) * 3 * 3] = _out_[2];
        sol[a + 2 + (b + 1) * 3 + (c + 1) * 3 * 3] = _out_[3];
        sol[a + 2 + (b + 2) * 3 + (c + 1) * 3 * 3] = _out_[4];
        sol[a + 2 + (b + 3) * 3 + (c + 1) * 3 * 3] = _out_[5];
        sol[a + 3 + (b + 1) * 3 + (c + 1) * 3 * 3] = _out_[6];
        sol[a + 3 + (b + 2) * 3 + (c + 1) * 3 * 3] = _out_[7];
      }
    }
  }
}