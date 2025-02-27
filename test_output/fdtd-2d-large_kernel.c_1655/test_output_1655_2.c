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
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (x = 0; x < 200; x++) {
      ex[x][0] = 1.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (y = 1; y < 240; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (x = 0; x < 200; x++) {
        ey[x][y] = ey[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 0; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (y = 1; y < 240; y++) {
        ex[x][y] = ex[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (x = 0; x < 200; x++) {
      int _in_tmp_;
      int _in_tmp_x_;
      int _in_tmp_y_;
      _in_tmp_ = 0 + 1;
      _in_tmp_x_ = x;
      _in_tmp_y_ = 0 + 1;
      ey[x][0] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (y = 1; y < 240; y++) {
        ey[x][y] = ey[x][y] - 0.5 * (_in_tmp_ * (ex[x][y] - ex[x][y - 1]) + _in_tmp_x_ * (ey[x][y] - ey[x][y - 1]) + _in_tmp_y_ * (hz[x][y] - hz[x][y - 1]));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (x = 0; x < 200; x++) {
      int _in_tmp_x;
      int _in_tmp_y;
      _in_tmp_x = x;
      _in_tmp_y = 0 + 1;
      ex[x][239] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (y = 238; y >= 1; y--) {
        ex[x][y] = ex[x][y] - 0.5 * (_in_tmp_x * (ey[x][y] - ey[x][y + 1]) + _in_tmp_y * (hz[x][y] - hz[x][y + 1]));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (x = 0; x < 200; x++) {
      int _in_tmp_x;
      int _in_tmp_y;
      _in_tmp_x = x;
      _in_tmp_y = 238 + 1;
      ey[x][239] = ey[x][239] - _in_tmp_x * (_fict_[x] - ex[x][239]);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      for (y = 238; y >= 1; y--) {
        ey[x][y] = ey[x][y] - _in_tmp_x * (ex[x][y] - ex[x][y + 1]) - _in_tmp_y * (hz[x][y] - hz[x][y + 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    for (x = 0; x < 200; x++) {
      int _in_tmp_x;
      int _in_tmp_y;
      _in_tmp_x = x;
      _in_tmp_y = 238 + 1;
      hz[x][0] = hz[x][0] - _in_tmp_y * (ey[x][0 + 1] - ey[x][0]);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      for (y = 1; y < 240; y++) {
        hz[x][y] = hz[x][y] - _in_tmp_x * (ex[x][y + 1] - ex[x][y]) - _in_tmp_y * (ey[x][y] - ey[x][y + 1]);
      }
    }
  }
}