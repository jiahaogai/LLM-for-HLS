

#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        double  _tmp_1 = 0.0;
        double  _tmp_2 = 0.0;
        double  _tmp_3 = 0.0;
        double  _tmp_4 = 0.0;
        double  _tmp_5 = 0.0;
        double  _tmp_6 = 0.0;
        double  _tmp_7 = 0.0;
        double  _tmp_8 = 0.0;
        double  _tmp_9 = 0.0;
        double  _tmp_10 = 0.0;
        double  _tmp_11 = 0.0;
        double  _tmp_12 = 0.0;
        double  _tmp_13 = 0.0;
        double  _tmp_14 = 0.0;
        double  _tmp_15 = 0.0;
        double  _tmp_16 = 0.0;
        double  _tmp_17 = 0.0;
        double  _tmp_18 = 0.0;
        double  _tmp_19 = 0.0;
        double  _tmp_20 = 0.0;
        double  _tmp_21 = 0.0;
        double  _tmp_22 = 0.0;
        double  _tmp_23 = 0.0;
        double  _tmp_24 = 0.0;
        double  _tmp_25 = 0.0;
        _tmp_1 = ex[i][j+1];
        _tmp_2 = ey[i][j+1];
        _tmp_3 = hz[i][j+1];
        _tmp_4 = ex[i][j];
        _tmp_5 = ey[i][j];
        _tmp_6 = hz[i][j];
        _tmp_7 = ex[i][j-1];
        _tmp_8 = ey[i][j-1];
        _tmp_9 = hz[i][j-1];
        _tmp_10 = ex[i+1][j];
        _tmp_11 = ey[i+1][j];
        _tmp_12 = hz[i+1][j];
        _tmp_13 = ex[i+1][j+1];
        _tmp_14 = ey[i+1][j+1];
        _tmp_15 = hz[i+1][j+1];
        _tmp_16 = ex[i+1][j-1];
        _tmp_17 = ey[i+1][j-1];
        _tmp_18 = hz[i+1][j-1];
        _tmp_19 = _tmp_6 - _tmp_5;
        _tmp_20 = _tmp_5 - _tmp_4;
        _tmp_21 = _tmp_4 - _tmp_3;
        _tmp_22 = _tmp_5 - _tmp_8;
        _tmp_23 = _tmp_8 - _tmp_7;
        _tmp_24 = _tmp_7 - _tmp_6;
        _tmp_25 = s_ex[0] * _tmp_19;
        ey[i][j] = _tmp_5 + ((_tmp_25 + s_ey[0] * _tmp_21) / (2.0));
        _hz[i][j] = _tmp_6 + ((_tmp_21 * (_tmp_20 - _tmp_24) + _tmp_25 * (_tmp_13 - _tmp_16)) / (_tmp_19 * (_tmp_12 - _tmp_15) - _tmp_22 * (_tmp_14 - _tmp_17)));
        _tmp_26 = _tmp_7 - _tmp_6;
        _tmp_27 = _tmp_8 - _tmp_7;
        _tmp_28 = _tmp_6 - _tmp_5;
        ex[i][j] = _tmp_4 + ((_tmp_27 * _tmp_26 + _tmp_28 * _tmp_24) / (_tmp_23 * _tmp_25 - _tmp_20 * _tmp_22));
      }
    }
  }
}
