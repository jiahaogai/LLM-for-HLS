
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
        double  delta_x = (double )(ex[i][j + 1] - ex[i][j]);
        double  delta_y = (double )(ey[i + 1][j] - ey[i][j]);
        double  delta_z = (double )(hz[i + 1][j] - hz[i][j]);
        double  si = delta_x - delta_y * 0.5;
        double  sj = delta_y + delta_x * 1j;
        double  sk = delta_x + delta_y * 0.5;
        double  _fj = _fict_[i * j];
        double  ei = -_fj * si;
        double  ej = -_fj * sj;
        double  ek = -_fj * sk;
        double  ux = 2.0 * (ei - ej * 1i) / (ei * ei + ej * ej);
        double  uy = 2.0 * (ej - ei * 1i) / (ei * ei + ej * ej);
        double  uz = 2.0 * (ek - ej * 1i) / (ek * ek + sj * sj);
        double  vx = 2.0 * (ei + ux * sj) / (si * si + ux * ux);
        double  vy = 2.0 * (ey[i][j] - uy * si) / (sj * sj + uy * uy);
        double  vz = 2.0 * (ek + uy * si) / (sk * sk + uy * uy);
        double  wx = 2.0 * (ek - vz * 1i) / (ek * ek + vz * vz);
        double  wy = 2.0 * (vz - ek * 1i) / (sk * sk + vz * vz);
        double  wz = 2.0 * (ek + vx * 1i) / (sk * sk + vx * vx);
        double  div = 4.0 + (double )uz * (ux * ux + vy * vy + wz * wz) + (double )vz * (ux * ux + vy * vy + vz * vz) + (double )wz * (ux * ux + vy * vy + vz * vz);
        ex[i][j] = vx;
        ey[i][j] = vy;
        hz[i][j] = wz;
        ex[i][j + 1] = vx + delta_x;
        ey[i + 1][j] = vy + delta_y;
        hz[i][j + 1] = wz + delta_z;
        ex[i + 1][j] = vx + delta_x;
        ey[i][j + 1] = vy + delta_y;
        hz[i + 1][j] = wz + delta_z;
        ex[i + 1][j + 1] = vx + delta_x;
        ey[i + 1][j + 1] = vy + delta_y;
        hz[i + 1][j + 1] = wz + delta_z;
        div[i][j] = div;
      }
    }
  }
}
