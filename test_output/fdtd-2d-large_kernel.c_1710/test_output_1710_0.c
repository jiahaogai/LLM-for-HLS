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
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (y = 1; y < 240 - 1; y++) {
        ey[x][y] = ey[x][y] - 0.5 * (hz[x][y + 1] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (y = 1; y < 240 - 1; y++) {
        ex[x][y] = ex[x][y] - 0.5 * (hz[x + 1][y] - hz[x - 1][y]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (y = 1; y < 240 - 1; y++) {
        hz[x][y] = hz[x][y] - 0.7 * (ex[x][y + 1] - ex[x][y - 1] + ey[x + 1][y] - ey[x - 1][y]);
      }
    }
  }
}