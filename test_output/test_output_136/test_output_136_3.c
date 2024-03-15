
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        z_x[i][j] = hz[i][j + 1] - hz[i][j];
        z_y[i][j] = hz[i + 1][j] - hz[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240 - 1; j++) {
        _x[0][j] = ex[i][j + 1] - ex[i][j];
        _y[0][j] = ey[i + 1][j] - ey[i][j];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L9}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      for (k = 1; k < 4; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
        for (j = 0; j < 240 - 1; j++) {
          _x[k][j] = _x[k][j] - 0.5 * (z_x[i + 1][j + 1] - z_x[i + 1][j]);
          _y[k][j] = _y[k][j] - 0.5 * (z_y[i + 1][j + 1] - z_y[i][j + 1]);
        }
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
      for (j = 0; j < 240 - 1; j++) {
        ey[i][j] = ((_x[0][j] + _y[0][j]) + ((_x[1][j] + _y[1][j]) + ((_x[2][j] + _y[2][j]) + _y[3][j]))) / 4.0;
        ex[i][j + 1] = ((_x[0][j] + _x[1][j]) + ((_y[0][j] + _x[2][j]) + ((_x[3][j] + _y[2][j]) + (_x[4][j] + _y[3][j])))) / 4.0;
      }
    }
  }
}
