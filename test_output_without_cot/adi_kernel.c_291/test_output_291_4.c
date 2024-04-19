#include "adi.h"
 #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DX_2;
  double DY_2;
  double DX_4;
  double DY_4;
  double DX_6;
  double DY_6;
  double DX_8;
  double DY_8;
  double NDX;
  double NDY;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double mul5;
  double mul6;
  double add1;
  double add2;
  double a;
  double b;
  double c;
  double d;
//#pragma scop
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  DX_8 = DX_4 * DX_4;
  DY_8 = DY_4 * DY_4;
  NDX = -1.0 * DX;
  NDY = -1.0 * DY;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 38; i++) {
      mul1 = DX_2 * v[i][0];
      mul2 = DY_2 * v[0][i];
      add1 = mul1 + mul2;
      a = u[i][0] + plus[0] * add1;
      b = u[i][39] + plus[1] * add1;
      c = (u[i][38] - q[i][38]) + plus[2] * add1;
      d = (u[i][1] - q[i][1]) + plus[3] * add1;
      p[i][0] = a + plus[4] * d;
      p[i][1] = b + plus[5] * d;
      p[i][2] = c + plus[6] * d;
      p[i][38] = c + plus[7] * d;
      p[i][37] = b + plus[8] * d;
      p[i][36] = a + plus[9] * d;
      mul3 = DX_2 * v[i][36];
      mul4 = DY_2 * v[36][i];
      add2 = mul3 + mul4;
      a = u[36][i] + plus[10] * add2;
      b = u[37][i] + plus[11] * add2;
      c = (u[38][i] - q[38][i]) + plus[12] * add2;
      d = (u[1][i] - q[1][i]) + plus[13] * add2;
      q[36][i] = a + plus[14] * d;
      q[37][i] = b + plus[15] * d;
      q[38][i] = c + plus[16] * d;
      q[1][i] = c + plus[17] * d;
      q[0][i] = b + plus[18] * d;
      q[1][i] = a + plus[19] * d;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j <= 38; j++) {
      mul5 = DX_2 * v[0][j];
      mul6 = DY_2 * v[j][0];
      tmp = mul5 + mul6;
      a = u[0][j] + plus[20] * tmp;
      b = u[39][j] + plus[21] * tmp;
      c = (u[38][j] - q[38][j]) + plus[22] * tmp;
      d = (u[37][j] - q[37][j]) + plus[23] * tmp;
      p[0][j] = a + plus[24] * d;
      p[1][j] = b + plus[25] * d;
      p[2][j] = c + plus[26] * d;
      p[38][j] = c + plus[27] * d;
      p[37][j] = b + plus[28] * d;
      p[36][j] = a + plus[29] * d;
      q[0][j] = a + plus[30] * d;
      q[1][j] = b + plus[31] * d;
      q[2][j] = c + plus[32] * d;
      q[38][j] = c + plus[33] * d;
      q[37][j] = b + plus[34] * d;
      q[36][j] = a + plus[35] * d;
    }
  }
//#pragma endscop
}