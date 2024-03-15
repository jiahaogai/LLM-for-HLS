 You have 4000000 elements.
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
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{64}
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
        double dxy_2 = ((ex[i][j + 1] - ex[i][j]) * (ey[i + 1][j] - ey[i][j])) + ((ey[i][j + 1] - ey[i][j]) * (ex[i + 1][j] - ex[i][j]));
        double dzt_2 = hz[i][j] - hz[i][j + 1];
        double dzq_2 = hz[i + 1][j] - hz[i + 1][j + 1];
        double dX_2 = ex[i][j + 1] - ex[i][j];
        double dY_2 = ey[i + 1][j] - ey[i][j];
        double dZ_2 = hz[i + 1][j + 1] - hz[i][j + 1];
        double nx_2 = dY_2 * dzq_2 - dZ_2 * dY_2;
        double ny_2 = dZ_2 * dX_2 - dX_2 * dzq_2;
        double nz_2 = dX_2 * dY_2 - dY_2 * dX_2;
        double s_2 = 1.0 / (1.0 + nx_2 + ny_2 + nz_2);
        double ex_2 = s_2 * (nx_2 * ex[i][j] + ny_2 * ex[i][j + 1] + nz_2 * ex[i + 1][j + 1] + nx_2 * ex[i + 1][j] + ny_2 * ex[i][j] + nz_2 * ex[i][j + 1] - dxy_2);
        double ey_2 = s_2 * (nx_2 * ey[i][j] + ny_2 * ey[i + 1][j] + nz_2 * ey[i + 1][j + 1] + nx_2 * ey[i + 1][j] + ny_2 * ey[i][j] + nz_2 * ey[i][j + 1] - dxy_2);
        double hz_2 = s_2 * (nx_2 * hz[i][j] + ny_2 * hz[i][j + 1] + nz_2 * hz[i + 1][j + 1] + nx_2 * hz[i + 1][j] + ny_2 * hz[i + 1][j] + nz_2 * hz[i][j] - dzq_2 - dzt_2);
        ex[i_col][j_col] = ex_2;
        ey[i_col][j_col] = ey_2;
        hz[i_col][j_col] = hz_2;
      }
    }
  }
}
