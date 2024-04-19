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
  DY = 1.0;
  DT = 1.0;
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DX * DX;
  mul2 = B2 * DY * DY;
  a = -mul1 / ((mul1 + mul2));
  b = -mul2 / ((mul1 + mul2));
  c = 1.0 + ((2.0 * mul1) / ((mul1 + mul2)));
  d = 1.0 + ((2.0 * mul2) / ((mul1 + mul2)));
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_tsteps:
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 40; t++) {
//#pragma ACCEL PIPELINE auto{__PIPE__L1}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j2:
    for (j = 1; j < 59; j++) {
      loop_i2:
      for (i = 1; i < 59; i++) {
        v[j][i] = -1.0 * (((u[j][i + 1] - u[j][i - 1]) / DX) + ((u[j + 1][i] - u[j - 1][i]) / DY));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j1:
    for (j = 1; j < 59; j++) {
      loop_i1:
      for (i = 1; i < 59; i++) {
        u[j][i] = u[j][i] + DT * ((a * v[j][i]) + (c * p[j][i]) - (d * q[j][i]));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_j3:
    for (j = 1; j < 59; j++) {
      loop_i3:
      for (i = 1; i < 59; i++) {
        p[j][i] = p[j][i] + DT * ((1.0 / Re) * (((d * v[j][i]) - (b * u[j][i])) - (p[j][i] * (v[j][i] - q[j][i]))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    loop_j4:
    for (j = 1; j < 59; j++) {
      loop_i4:
      for (i = 1; i < 59; i++) {
        q[j][i] = q[j][i] + DT * ((1.0 / Re) * ((b * u[j][i]) - (d * v[j][i]) - (q[j][i] * (v[j][i] - p[j][i]))));
      }
    }
  }
}