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
        double  delta_z = (double )(hz[i][j + 1] - hz[i][j]);
        double   si = 1.0 / (1.0 + delta_x * delta_x);
        double   sj = 1.0 / (1.0 + delta_y * delta_y);
        double   sk = 1.0 / (1.0 + delta_z * delta_z);
        double  val = si * sj * sk * (hz[i][j] - (delta_x * ((ey[i][j + 1] - ey[i][j]) + (delta_y * (ex[i + 1][j] - ex[i][j])))) - delta_z * (ex[i][j] - ex[i][j + 1]));
        double  ex_x = si * sj * ( ey[i][j + 1] - ey[i][j] - delta_x * (val - ex[i][j]));
        double  ey_y = sj * sk * ( ex[i + 1][j] - ex[i][j] - delta_y * (val - ey[i][j]));
        double  hz_z = sk * si * ( ex[i][j] - ex[i][j + 1] - delta_z * (val - hz[i][j]));
        ex[i][j] = ex_x;
        ey[i][j] = ey_y;
        hz[i][j] = hz_z;
      }
    }
  }
}