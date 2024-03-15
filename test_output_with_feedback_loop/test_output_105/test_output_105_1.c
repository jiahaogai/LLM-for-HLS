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
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
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
        double  _val_1 = 0.0;
        double  _val_2 = 0.0;
        double  _val_3 = 0.0;
        double  _val_4 = 0.0;
        double  _val_5 = 0.0;
        double  _val_6 = 0.0;
        double  _val_7 = 0.0;
        double  _val_8 = 0.0;
        double  _val_9 = 0.0;
        _val_1 = ex[i][j + 1] - ex[i][j];
        _val_2 = ey[i + 1][j] - ey[i][j];
        _val_3 = hz[i][j + 1] - hz[i][j];
        _val_4 = hz[i + 1][j] - hz[i][j];
        _val_5 = ex[i][j + 1] - ex[i][j];
        _val_6 = ey[i + 1][j + 1] - ey[i + 1][j];
        _val_7 = ey[i][j] - ey[i][j + 1];
        _val_8 = hz[i + 1][j + 1] - hz[i][j + 1];
        _val_9 = hz[i + 1][j] - hz[i][j];
        ey[i][j] = _val_9 + _fict_[i * nx + j] + 0.25 * (_val_6 - _val_7);
        _fict_[i * nx + j] = _val_3 + _fict_[i * nx + j] + 0.25 * (_val_4 - _val_1);
        ex[i][j] = _val_7 + _fict_[i * nx + j] + 0.25 * (_val_2 - _val_8);
      }
    }
  }
}