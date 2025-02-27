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
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (x = 1; x < 200 - 1; x++) {
      ey[0][x] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (y = 1; y < 240 - 1; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (x = 1; x < 200 - 1; x++) {
        ey[x][y] = ey[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 1; x < 200 - 1; x++) {
      ex[x][0] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (y = 1; y < 240 - 1; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (x = 1; x < 200 - 1; x++) {
        ex[x][y] = ex[x][y] - 0.5 * (hz[x][y] - hz[x - 1][y]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (x = 1; x < 200 - 1; x++) {
      hz[x][0] = hz[x][0] - 0.5 * (ex[x][0] - ex[x][1]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (y = 1; y < 240 - 1; y++) {
      hz[0][y] = hz[0][y] - 0.5 * (ey[0][y] - ey[1][y]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (x = 1; x < 200 - 1; x++) {
      for (y = 1; y < 240 - 1; y++) {
        ey[x][y] = ey[x][y] - 0.7 * (ex[x][y] - ex[x][y + 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (x = 1; x < 200 - 1; x++) {
      for (y = 1; y < 240 - 1; y++) {
        ex[x][y] = ex[x][y] - 0.7 * (ey[x][y] - ey[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    for (x = 1; x < 200 - 1; x++) {
      for (y = 1; y < 240 - 1; y++) {
        hz[x][y] = hz[x][y] - 0.7 * (hz[x][y] - hz[x - 1][y]);
      }
    }
  }
}