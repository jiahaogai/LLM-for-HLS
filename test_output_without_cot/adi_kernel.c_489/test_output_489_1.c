#include "adi.h"
 #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DT;
  double B1;
  double B2;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  DY = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DT = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B1 = 2.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B2 = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul1 = B1 * DX * DY;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul2 = B2 * DX * DY;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  a = -mul1 / ((DX * DX) + (DY * DY));
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  b = -mul2 / ((DX * DX) + (DY * DY));
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  c = 2.0 - (2.0 * B1 / ((DX * DX) + (DY * DY)));
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  d = 2.0 - (2.0 * B2 / ((DX * DX) + (DY * DY)));
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (t = 1; t <= 39; t++) {
// Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * (p[i][j - 1] + p[i][j + 1]) + u[j][i];
        q[i][j] = -b * (q[i][j - 1] + q[i][j + 1]) + v[j][i];
      }
      v[60 -1][i] = 1.0;
    }
// Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        p[i][j] = c * (p[i][j - 1] - d * p[i][j + 1]) + u[j][i];
        q[i][j] = d * (q[i][j - 1] - a * q[i][j + 1]) + v[j][i];
      }
      u[i][60 -1] = 1.0;
    }
  }
}