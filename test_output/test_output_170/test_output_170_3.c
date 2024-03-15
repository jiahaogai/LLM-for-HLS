
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
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
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
        double dxy_x = 0.5 * (ex[i + 1][j + 1] - ex[i + 1][j - 1]);
        double dxy_y = 0.5 * (ey[i + 1][j + 1] - ey[i - 1][j + 1]);
        double dzz_x = 0.5 * (hz[i + 1][j + 1] - hz[i + 1][j - 1]);
        double dzz_y = 0.5 * (hz[i + 1][j + 1] - hz[i - 1][j + 1]);
        double ex_x = ex[i][j] + 0.7071 * dxy_x - 0.5661 * dzz_x;
        double ex_y = ey[i][j] + 0.7071 * dxy_y + 0.5661 * dzz_x;
        double ey_x = ex[i][j] - 0.7071 * dxy_x + 0.5661 * dzz_y;
        double ey_y = ey[i][j] - 0.7071 * dxy_y - 0.5661 * dzz_y;
        double hz_x = hz[i][j] + 1.0 * dzz_x + 1.0 * dxy_y;
        double hz_y = hz[i][j] + 1.0 * dzz_y - 1.0 * dxy_x;
        ex[i][j + 1] = ex_x;
        ey[i + 1][j] = ey_y;
        ey[i][j] = ey_x;
        hz[i][j] = hz_x;
        hz[i + 1][j] = hz_y;
      }
    }
  }
}
