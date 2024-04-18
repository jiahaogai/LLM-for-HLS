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
    for (x = 1; x < 200 - 1; x++) {
      ey[x][1] = ey[x][1] - 0.5 * (hz[x][1] - hz[x][0]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (y = 1; y < 240 - 1; y++) {
      ex[1][y] = ex[1][y] - 0.5 * (hz[1][y] - hz[0][y]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (y = 1; y < 240 - 1; y++) {
        hz[x][y] = hz[x][y] - 0.7 * (ex[x][y] - ex[x][y - 1]) - 0.7 * (ey[x][y] - ey[x - 1][y]) + _fict_[x][y];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (x = 1; x < 200 - 1; x++) {
      ey[x][240 - 1] = ey[x][240 - 1] - 0.5 * (hz[x][240 - 1] - hz[x][240 - 2]);
    }
  }
}