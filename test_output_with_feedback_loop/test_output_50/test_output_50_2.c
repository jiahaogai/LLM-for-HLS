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
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
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
        int i_col = -1;
        int j_col = -1;
        double dxy_2 = ex[i][j] * ex[i][j] + ey[i][j] * ey[i][j];
        double dzt_2 = hz[i][j] * hz[i][j] + hz[i][j + 1] * hz[i][j + 1] + hz[i + 1][j] * hz[i + 1][j] + hz[i + 1][j + 1] * hz[i + 1][j + 1];
        double rho = dzt_2 / (dzt_2 + 0.5);
        double tmp = rho * (hz[i][j + 1] * ey[i][j + 1] - hz[i + 1][j + 1] * ey[i + 1][j + 1] + hz[i][j] * ey[i][j] - hz[i + 1][j] * ey[i + 1][j]);
        double tmp_2 = rho * (hz[i + 1][j] * ex[i + 1][j] - hz[i][j] * ex[i][j] + hz[i + 1][j + 1] * ex[i + 1][j + 1] - hz[i][j + 1] * ex[i][j + 1]);
        double dxx = dxy_2;
        double dyy = dxy_2;
        double dzx = tmp_2 + ex[i][j] * (-1.0 * (hz[i + 1][j + 1] + hz[i][j + 1]) + hz[i + 1][j] + hz[i][j]);
        double dzy = tmp_2 + ey[i][j] * (-1.0 * (hz[i + 1][j + 1] + hz[i][j + 1]) + hz[i + 1][j + 1] + hz[i][j + 1]);
        double dzz = 4.0 * (hz[i][j] - hz[i][j + 1] - hz[i + 1][j] + hz[i + 1][j + 1]);
        ex[i][j] = dxx - dzx;
        ey[i][j] = dyy - dzy;
        hz[i][j] = dzz + tmp;
      }
    }
  }
}