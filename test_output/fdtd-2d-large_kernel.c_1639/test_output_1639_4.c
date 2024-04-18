### ACCEL kernel
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (x = 0; x < 200; x++) {
      ex[x][0] = 1.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (y = 1; y < 240; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (x = 0; x < 200; x++) {
        ey[x][y] = ey[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (x = 0; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (y = 1; y < 240; y++) {
        ex[x][y] = ex[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (x = 0; x < 200; x++) {
      int _in_val_;
      _in_val_ = 0;
      
#pragma ACCEL PARALLEL reduction=_in_val_ FACTOR=auto{__PARA__L7}
      for (y = 0; y < 240; y++) {
        _in_val_ += ey[x][y] * _fict_[y];
      }
      hz[x][0] = _fict_[0] - _in_val_;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (y = 0; y < 240; y++) {
      int _in_val_;
      _in_val_ = 0;
      
#pragma ACCEL PARALLEL reduction=_in_val_ FACTOR=auto{__PARA__L9}
      for (x = 0; x < 200; x++) {
        _in_val_ += ex[x][y] * hz[x][y];
      }
      ey[0][y] = _fict_[y + 1] - _in_val_;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L10}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
    for (x = 1; x < 200; x++) {
      int _in_val_;
      _in_val_ = 0;
      
#pragma ACCEL PARALLEL reduction=_in_val_ FACTOR=auto{__PARA__L11}
      for (y = 0; y < 240; y++) {
        _in_val_ += ex[x][y] * ey[x][y];
      }
      hz[x][0] = -_in_val_;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L12}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
    for (y = 1; y < 240; y++) {
      int _in_val_;
      _in_val_ = 0;
      
#pragma ACCEL PARALLEL reduction=_in_val_ FACTOR=auto{__PARA__L13}
      for (x = 0; x < 200; x++) {
        _in_val_ += ey[x][y] * hz[x][y];
      }
      ex[0][y] = _fict_[y + 1] - _in_val_;
    }
  }
}