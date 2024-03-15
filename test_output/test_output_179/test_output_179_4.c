 The C codes are provided below:

 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
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
        double  delta = 1.0 / ((double )(1 << 12));
        double  p1 = ex[i][j] - ex[i][j + 1];
        double  p2 = ey[i][j] - ey[i + 1][j];
        double  p3 = hz[i][j] - hz[i + 1][j];
        double  p4 = hz[i][j + 1] - hz[i + 1][j + 1];
        double  Dx = (-p1 + p2) * delta;
        double  Dy = (-p2 + p3) * delta;
        double  Dz = (p3 - p4) * delta;
        double  ex_x = Dx * ex[i][j] + Dy * ex[i][j + 1] + Dz * ex[i][j + 1];
        double  ey_y = Dy * ey[i][j] + Dx * ey[i + 1][j] + Dz * ey[i][j + 1];
        double  hz_z = Dz * hz[i][j] + Dy * hz[i][j + 1] + Dx * hz[i + 1][j + 1];
        double  ex_x_p1 = Dx * ex_x + Dy * ey_y + Dz * hz_z;
        ex[i][j] = ex_x - ex_x_p1 * 1.0;
        ey[i][j] = ey_y - ex_x_p1;
        hz[i][j] = hz_z - ex_x_p1;
      }
    }
  }
}
