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
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
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
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 0; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (y = 1; y < 240; y++) {
        ex[x][y] = ex[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (z = 0; z < 200; z++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (y = 0; y < 240 - 2; y++) {
        ey[z][y] = ey[z][y] - 0.7 * (ex[z][y + 2] - ex[z][y]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (x = 0; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (y = 0; y < 240 - 2; y++) {
        ex[x][y] = ex[x][y] - 0.7 * (ey[x][y + 2] - ey[x][y]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (z = 0; z < 200; z++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (y = 0; y < 240 - 2; y++) {
        hz[z][y] = hz[z][y] - 1.0 * (ex[z][y + 2] - ex[z][y]) - 0.5 * (ey[z][y + 2] - ey[z][y]) + _fict_[z];
      }
    }
  }
}