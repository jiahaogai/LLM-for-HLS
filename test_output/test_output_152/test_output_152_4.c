

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
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
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
        double  delx =  (double )(ex[i + 1][j + 1] - ex[i][j + 1]);
        double  dely =  (double )(ey[i + 1][j + 1] - ey[i][j + 1]);
        double  delz =  (double )(hz[i + 1][j + 1] - hz[i][j + 1]);
        double  icoef =  - 1.0 / 3.0;
        double  x1 = delx + icoef * (dely * (hz[i + 1][j + 1] - hz[i + 1][j]) - delz * (ey[i + 1][j + 1] - ey[i + 1][j]));
        double  y1 = dely + icoef * (delz * (ex[i + 1][j + 1] - ex[i][j + 1]) - delx * (hz[i + 1][j + 1] - hz[i][j + 1]));
        double  x2 = icoef * (dely * (hz[i][j + 1] - hz[i][j]) - delz * (ey[i][j + 1] - ey[i][j]));
        double  y2 = icoef * (delz * (ex[i][j + 1] - ex[i][j]) - delx * (hz[i][j + 1] - hz[i][j]));
        double  jac = 0.5 * (delx * (dely + x2) + dely * (delz + y2) + delz * (delx + x1));
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
	for (v = 0; v < 40; v++) {
          hz[i][j] +=  (((double )(se[v] * (ex[i][j] - ex[i][j] + ey[i][j] - ey[i][j] + hz[i][j] - hz[i][j]))) / jac);
        }
      }
    }
  }
}