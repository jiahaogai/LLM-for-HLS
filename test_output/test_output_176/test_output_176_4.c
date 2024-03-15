
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
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
        zx[i][j] = sqrt((ex[i][j + 1] - ex[i][j]) * (ex[i][j + 1] - ex[i][j]) + (ey[i + 1][j] - ey[i][j]) * (ey[i + 1][j] - ey[i][j])) / (hx * hy);
        zy[i][j] = sqrt((ey[i + 1][j] - ey[i][j]) * (ey[i + 1][j] - ey[i][j]) + (ex[i][j + 1] - ex[i][j]) * (ex[i][j + 1] - ex[i][j])) / (hx * hy);
        hz[i][j] = hz[i][j] + 1.0 / (2.0 * (1.0 + zx[i][j] * zy[i][j])) * (qx[i][j + 1] - qx[i][j] + qy[i + 1][j] - qy[i][j] - zx[i][j] * ((ex[i][j + 1] - ex[i][j]) / (hx * hy)) - zy[i][j] * ((ey[i + 1][j] - ey[i][j]) / (hx * hy)));
      }
    }
  }
}
