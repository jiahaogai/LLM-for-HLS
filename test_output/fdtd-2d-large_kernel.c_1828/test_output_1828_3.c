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
      ey[x][0] = 1.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (y = 1; y < 240; y++) {
      ex[0][y] = ex[0][y] - ex[0][y - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 1; x < 200; x++) {
      ey[x][0] = ey[x][0] - ey[x - 1][0];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (y = 1; y < 240; y++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (x = 1; x < 200; x++) {
        ey[x][y] = ey[x][y] - (hz[x][y] - hz[x][y - 1]);
        ex[y][x] = ex[y][x] - (hz[x][y] - hz[x - 1][y]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (x = 0; x < 200; x++) {
      ey[x][0] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (y = 0; y < 240; y++) {
      ex[0][y] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (x = 0; x < 200; x++) {
      for (y = 0; y < 240; y++) {
        hz[x][y] = hz[x][y] - (ex[x][y] + ey[x][y]);
      }
    }
  }
}