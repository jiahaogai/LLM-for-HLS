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
    for (z = 0; z < 100; z++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (x = 0; x < 200; x++) {
        hz[x][0] = hz[x][0] - 0.5 * (ex[x][0] - _fict_[z]);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (y = 1; y < 240; y++) {
        for (x = 0; x < 200; x++) {
          hz[x][y] = hz[x][y] - 0.5 * (ey[x][y] - ey[x][y - 1]) * (hz[x][y] - hz[x][y - 1]);
        }
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (x = 0; x < 200; x++) {
        hz[x][239] = hz[x][239] - 0.5 * (ey[x][239] - ey[x][238]) * (hz[x][239] - hz[x][238]);
      }
    }
  }
}