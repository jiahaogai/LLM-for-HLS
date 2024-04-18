### AutoPIPE line:
 
#pragma ACCEL PIPELINE auto{off}

### End of AutoPIPE line

### AutoTILE line:
 #pragma ACCEL TILE FACTOR=auto{1}

### End of AutoTILE line

#pragma ACCEL PARALLEL FACTOR=auto{1}

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
      ex[0][y] = ex[0][y] - ex[0][y - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 1; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (y = 0; y < 240; y++) {
        ey[x][y] = ey[x][y] - 0.5 * (hz[x][y] - hz[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (x = 0; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (y = 1; y < 240; y++) {
        ez[x][y] = ez[x][y] - 0.5 * (ex[x][y] - ex[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (x = 1; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (y = 1; y < 240; y++) {
        ex[x][y] = ex[x][y] - 0.7 * (ey[x][y] - ey[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    for (x = 1; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      for (y = 1; y < 240; y++) {
        ey[x][y] = ey[x][y] - 0.7 * (ez[x][y] - ez[x][y - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L11}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L11}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
    for (x = 1; x < 200; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
      for (y = 1; y < 240; y++) {
        ez[x][y] = ez[x][y] - 0.7 * (ex[x][y] - ex[x - 1][y] - ey[x][y] + ey[x][y - 1]);
      }
    }
  }
}