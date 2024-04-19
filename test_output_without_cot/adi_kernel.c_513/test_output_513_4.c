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
  double tmp;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      d = DX_2 * (2.0 * u[i][0] - u[i][1] - u[i][2] + u[i][3]);
      e = DX_2 * (u[i][1] - u[i][2]);
      f = DX_2 * (u[i][2] - u[i][3]);
      a = DY_2 * (2.0 * v[0][i] - v[1][i] - v[3][i] + v[4][i]);
      b = DY_2 * (v[1][i] - v[3][i]);
      c = DY_2 * (v[3][i] - v[4][i]);
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        tmp = d * p[j][0] - e * p[j][1] - f * p[j][2] + a * q[j][0] - b * q[j][1] - c * q[j][2];
        v[0][i] =  - d * p[j][1] + e * (p[j][0] + p[j][2]) - f * p[j][3] + a * q[j][1] + b * (q[j][0] + q[j][2]) - c * q[j][3];
        v[1][i] =  d * q[j][1] - e * q[j][0] + f * q[j][2] + a * p[j][1] - b * p[j][0] + c * p[j][2];
        v[2][i] =  d * p[j][2] - e * q[j][2] + f * q[j][3] + a * q[j][1] - b * q[j][3] + c * q[j][0];
        v[3][i] =  d * q[j][2] - e * q[j][3] + f * q[j][0] + a * p[j][3] - b * q[j][3] + c * q[j][0];
        v[4][i] = tmp;
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (i = 1; i < 59; i++) {
      d = DY_2 * (2.0 * u[0][i] - u[1][i] - u[3][i] + u[4][i]);
      e = DY_2 * (u[1][i] - u[3][i]);
      f = DY_2 * (u[3][i] - u[4][i]);
      a = DX_2 * (2.0 * v[i][0] - v[i][1] - v[i][2] + v[i][3]);
      b = DX_2 * (v[i][1] - v[i][2]);
      c = DX_2 * (v[i][2] - v[i][3]);
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        u[0][j] =  - d * p[j][1] + e * (p[j][0] + p[j][2]) - f * p[j][3] + a * q[j][1] + b * (q[j][0] + q[j][2]) - c * q[j][3];
        u[1][j] =  d * q[j][1] - e * q[j][0] + f * q[j][2] + a * p[j][1] - b * p[j][0] + c * p[j][2];
        u[2][j] =  d * p[j][2] - e * q[j][2] + f * q[j][3] + a * q[j][1] - b * q[j][3] + c * q[j][0];
        u[3][j] =  d * q[j][2] - e * q[j][3] + f * q[j][0] + a * p[j][3] - b * q[j][3] + c * q[j][0];
        q[0][j] =  - d * v[i][1] + e * v[i][0] - f * v[i][2] + a * p[j][1] - b * p[j][0] + c * p[j][2];
        q[1][j] =  d * p[j][1] - e * p[j][0] + f * p[j][2] + a * v[i][1] - b * v[i][0] + c * v[i][2];
        q[2][j] =  d * v[i][2] - e * v[i][3] + f * v[i][0] + a * q[j][2] - b * q[j][3] + c * q[j][0];
        q[3][j] =  d * v[i][3] - e * v[i][4] + f * v[i][0] + a * q[j][3] - b * q[j][4] + c * q[j][0];
      }
    }
  }
//#pragma endscop
}