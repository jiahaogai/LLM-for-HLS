#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 240; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (i = 0; i < 200; i++) {
        ey[i][j] = ey[i][j] + 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (j = 0; j < 240; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (i = 0; i < 200; i++) {
        ex[i][j] = ex[i][j] + 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 1; j < 240; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (i = 0; i < 200; i++) {
        hz[i][j] = hz[i][j] - 0.5 * (ex[i][j] - ex[i][j - 1]) + 0.5 * (ey[i][j] - ey[i][j - 1]);
      }
    }
  }
}