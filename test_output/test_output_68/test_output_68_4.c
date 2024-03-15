
 
#pragma ACCEL kernel

void kernel_mvt(double x[400],double y[400],double u1[400],double u2[400],double v1[400],double v2[400],int up[400],int vp[400],int nz)
{
  int i;
  int k;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 400; i++) {
    x[i] = ((double )0);
    y[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 400; i++) {
    int _in_x2;
    int _in_x3;
    _in_x2 = ((int )u1[i]) - 1;
    _in_x3 = ((int )v1[i]) - 1;
    for (k = 0; k < 30; k++) {
      int _in_x4;
      double _in_x5;
      double _in_x6;
      double _in_x7;
      double _in_x8;
      double _in_x9;
      double _in_x10;
      double _in_x11;
      double _in_x12;
      double _in_x13;
      double _in_x14;
      double _in_x15;
      double _in_x16;
      double _in_x17;
      double _in_x18;
      double _in_x19;
      double _in_x20;
      double _in_x21;
      double _in_x22;
      double _in_x23;
      double _in_x24;
      double _in_x25;
      double _in_x26;
      double _in_x27;
      double _in_x28;
      double _in_x29;
      double _in_x30;
      _in_x4 = _in_x2 + ((int )u2[i]) * nz;
      _in_x5 = x[_in_x4];
      _in_x6 = y[_in_x4];
      _in_x7 = ((double )(up[k] - _in_x2));
      _in_x8 = _in_x7 * _in_x7;
      _in_x9 = 2.0 * _in_x7 * _in_x6;
      _in_x10 = _in_x8 * _in4;
      _in_x11 = _in_x8 * _in5;
      _in_x12 = 2.0 * _in_x6;
      _in_x13 = _in_x9 * _in4;
      _in_x14 = _in_x9 * _in5;
      _in_x15 = _in_x7 * _in6;
      _in_x16 = _in_x8 * _in6;
      _in_x17 = _in_x7 * _in7;
      _in_x18 = _in_x8 * _in7;
      _in_x19 = _in_x6 * _in4;
      _in_x20 = _in_x6 * _in5;
      _in_x21 = _in_x6 * _in6;
      _in_x22 = _in_x7 * _in8;
      _in_x23 = _in_x8 * _in8;
      _in_x24 = _in_x6 * _in9;
      _in_x25 = _in_x7 * _in9;
      _in_x26 = _in_x8 * _in10;
      _in_x27 = _in_x6 * _in10;
      _in_x28 = _in_x7 * _in11;
      _in_x29 = _in_x8 * _in11;
      _in_x30 = _in_x6 * _in12;
      temp = _in_x10 + _in_x11 + _in_x12;
      x[_in_x4] = _in_x5 + _in_x13 + _in_x14 + _in_x15;
      y[_in_x4] = _in_x6 + _in_x16 + _in_x17 + _in_x18;
      x[(_in_x4 + _in_x2)] = _in_x5 + _in_x19 + _in_x20 + _in_x21;
      y[(_in_x4 + _in_x2)] = _in_x6 + _in_x22 + _in_x23 + _in_x24;
      x[(_in_x4 + _in_x3)] = _in_x5 + _in_x25 + _in_x26 + _in_x27;
      y[(_in_x4 + _in_x3)] = _in_x6 + _in_x28 + _in_x29 + _in_x30;
    }
  }
}
