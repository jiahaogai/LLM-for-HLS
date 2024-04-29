#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double _in[8];
  double _out[8];
  double _tmp_0;
  double _tmp_1;
  double _tmp_2;
  double _tmp_3;
  double _tmp_4;
  double _tmp_5;
  double _tmp_6;
  double _tmp_7;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (int t = 0; t < 27; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (int i = 0; i < 3; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          _in[k] = orig[k - 1 + 3 * (j - 1 + 3 * (i - 1))];
        }
        _tmp_0 = _in[0] + _in[1] + _in[2];
        _tmp_1 = _in[3] + _in[4] + _in[5];
        _tmp_2 = _in[6] + _in[7];
        _tmp_3 = _tmp_1 + _tmp_2;
        _tmp_4 = _tmp_0 + _tmp_3;
        _tmp_5 = _tmp_4 * 0.125;
        _out[0] = _tmp_5;
        _tmp_6 = _in[3] + _in[4] + _in[5] + _in[6] + _in[7];
        _tmp_7 = _tmp_6 * 0.125;
        _out[3] = _tmp_7;
        _out[1] = _tmp_5;
        _out[2] = _tmp_5;
        _out[4] = _tmp_7;
        _out[5] = _tmp_7;
        _out[7] = _tmp_7;
        _out[6] = _tmp_7;
        for (int k = 0; k < 8; k++) {
          sol[k + 3 * (j + 3 * (i + 3 * 0))];
          _out[k];
        }
      }
    }
  }
}