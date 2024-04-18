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
    for (j = 0; j < 240; j++) {
      ey[0][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (y = 1; y < 200; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (x = 0; x < 240; x++) {
        ey[y][x] = ey[y][x] - 0.5 * (hz[y][x] - hz[y - 1][x]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 0; x < 240; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (y = 0; y < 200; y++) {
        ex[y][x] = ex[y][x] - 0.5 * (hz[y][x] - hz[y][x - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (y = 0; y < 200; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (x = 1; x < 240; x++) {
        hz[y][x] = hz[y][x] - 0.7 * (ex[y][x] - ex[y][x - 1]) - 0.7 * (ey[y][x] - ey[y][x - 1]);
      }
    }
  }
}