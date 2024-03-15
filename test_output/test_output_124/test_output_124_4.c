
 
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
        double delta_e = (ex[i][j + 1] - ex[i][j]) + (ey[i + 1][j] - ey[i][j]);
        double  delta_h = hz[i][j + 1] - hz[i][j];
        double  Dx = dcx[i] * delta_e;
        double  Dy = dcy[j] * delta_e;
        double  Dz = dcz[i] * delta_h;
        double  Dx2 = Dx * Dx;
        double  Dy2 = Dy * Dy;
        double  Dz2 = Dz * Dz;
        double  R = sqrt((Dx2 + Dy2 + Dz2));
        double  e = 50.0 * (Dz2 - Dy2);
        double  f = 50.0 * (Dx2 - Dy2);
        double  g = 50.0 * (Dx2 + Dy2 - Dz2);
        double  Jx = Dx*(-e + 2.0*f) - Dy*(g - 2.0*Dz) - Dz*2.0*Dx*Dy;
        double  Jy = Dy*(-e + 2.0*f) - Dx*(g - 2.0*Dz) - Dz*2.0*Dy*Dx;
        double  Jz = Dz*(-e + 2.0*f) - Dx*g + Dy*Dz - 2.0*Dz2*Dx - 2.0*Dy2*Dy;
        ex[i][j] = ex[i][j] + 0.7 * Jx;
        ey[i][j] = ey[i][j] + 0.7 * Jy;
        hz[i][j] = hz[i][j] + 0.7 *(Jz - 0.005 * R);
      }
    }
  }
}
