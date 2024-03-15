#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
        double  _vala = 0.0;
        double  _valb = 0.0;
        double  _valc = 0.0;
        double  _vald = 0.0;
        double  _vale = 0.0;
        double  _valf = 0.0;
        double  _valg = 0.0;
        double  _valh = 0.0;
        _vala = ex[i][j];
        _valb = ey[i][j];
        _valc = hz[i][j];
        _vald = ex[i][j + 1];
        _vale = ey[i][j + 1];
        _valf = hz[i][j + 1];
        _valg = ex[i + 1][j];
        _valh = ey[i + 1][j];
        hz[i][j] = _valc + 0.25 * (sqr(sin(_vala)) * (_valb - _valh) + sqr(sin(_valb)) * (_vala - _valg) + sqr(sin(_valc)) * (_valh - _vald) + sqr(sin(_vald)) * (_valg - _vala) + sqr(sin(_vale)) * (_valb - _valf) + sqr(sin(_valf)) * (_vale - _valb) + sqr(sin(_valg)) * (_vald - _valc) + sqr(sin(_valh)) * (_valc - _vald));
        ey[i][j] = _valb + 0.25 * (sqr(sin(_vala)) * (hz[i][j] - _vald) + sqr(sin(_valb)) * (hz[i][j + 1] - _vale) + sqr(sin(_valc)) * (hz[i + 1][j] - _valf) + sqr(sin(_vald)) * (hz[i][j] - _valg) + sqr(sin(_vale)) * (hz[i][j + 1] - _vala) + sqr(sin(_valf)) * (hz[i + 1][j + 1] - _valb) + sqr(sin(_valg)) * (hz[i + 1][j] - _valc) + sqr(sin(_valh)) * (hz[i + 1][j + 1] - _vald));
        ex[i][j] = _vala + 0.25 * (sqr(sin(_vala)) * (hz[i][j + 1] - _valf) + sqr(sin(_valb)) * (hz[i + 1][j + 1] - _valg) + sqr(sin(_valc)) * (hz[i + 1][j] - _valh) + sqr(sin(_vald)) * (hz[i][j] - _vala) + sqr(sin(_vale)) * (hz[i + 1][j + 1] - _valb) + sqr(sin(_valf)) * (hz[i][j + 1] - _vale) + sqr(sin(_valg)) * (hz[i + 1][j] - _valc) + sqr(sin(_valh)) * (hz[i + 1][j + 1] - _vald));
      }
    }
  }
}