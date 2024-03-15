#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
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
        double delta_x = (double )(ex[i][j + 1] - ex[i][j]);
        double  delta_y = (double )(ey[i + 1][j] - ey[i][j]);
        double  delta_z = (double )(hz[i + 1][j] - hz[i][j]);
        double  si_x = delta_x / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  si_y = delta_y / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  si_z = delta_z / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  xi_x = -1.0 * delta_x / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  xi_y = -1.0 * delta_y / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  xi_z = -1.0 * delta_z / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  _in_1 = si_x * (hz[i][j] - hz[i][j + 1]);
        double  _in_2 = si_y * (hz[i][j] - hz[i + 1][j]);
        double  _in_3 = si_z * (hz[i][j] - hz[i + 1][j + 1]);
        double  _in_4 = xi_x * (_in_1 + _in_2);
        double  _in_5 = xi_y * (_in_1 + _in_3);
        double  _in_6 = xi_z * (_in_1 + _in_2 + _in_3);
        ey[i][j] = ey[i][j] + _in_4;
        ex[i][j] = ex[i][j] + _in_5;
        hz[i][j] = hz[i][j] + _in_6;
      }
    }
  }
}