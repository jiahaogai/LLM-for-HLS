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
  double DT;
  double DT_2;
  double DT_4;
  double C1;
  double C2;
  double C4;
  double C5;
  double Coef_1;
  double Coef_2;
  double Coef_3;
  double Coef_4;
  double E;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  DX = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  DY = 1.0;
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  DX_8 = DX_4 * DX_4;
  DY_8 = DY_4 * DY_4;
  DT = 0.015;
  DT_2 = DT * DT;
  DT_4 = DT_2 * DT_2;
  C1 = DT_2 / DX_2;
  C2 = DT_2 / DY_2;
  C4 = 1.0 / (2.0 * (1.0 + DX_2 + DY_2));
  C5 = 1.0 / (2.0 * (1.0 + DX_2 + DY_2));
  Coef_1 = C1 + 2.0 * C2 + C4;
  Coef_2 = 2.0 * (C1 + C2);
  Coef_3 = C1 + C2;
  Coef_4 = 4.0 * C5;
  E = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 1; j < 59; j++) {
        E = ((double )(((int )u[j][i]) - ((int )q[j][i - 1])));
        p[i][j] = -1.0 / DX_2 * (p[i][j - 1] - E * ((double )(((int )u[j][i - 1]) - ((int )q[j][i - 1])) / DX)) - 1.0 / DY_2 * (p[i][j + 1] - E * ((double )(((int )u[j + 1][i]) - ((int )q[j + 1][i])) / DY));
        q[i][j] = -1.0 / DX_2 * (v[j][i] - E * ((double )(((int )u[j][i - 1]) - ((int )p[i][j - 1])) / DX)) - 1.0 / DY_2 * (v[j][i] - E * ((double )(((int )u[j + 1][i]) - ((int )p[i][j + 1])) / DY)) - C4 / (1.0 + 2.0 * DX_2 + DY_2) * (p[i][j] - p[i][j - 1]);
      }
      v[60 - 1][i] = 1.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        E = ((double )(((int )v[i][j]) - ((int )q[i][j - 1])));
        p[i][j] = -1.0 / DY_2 * (p[i][j - 1] - E * ((double )(((int )u[i][j - 1]) - ((int )q[i][j - 1])) / DY)) - 1.0 / DX_2 * (p[i + 1][j] - E * ((double )(((int )u[i + 1][j]) - ((int )q[i + 1][j])) / DX));
        q[i][j] = -1.0 / DY_2 * (u[i][j] - E * ((double )(((int )u[i][j - 1]) - ((int )p[i][j - 1])) / DY)) - 1.0 / DX_2 * (u[i][j] - E * ((double )(((int )u[i + 1][j]) - ((int )p[i + 1][j])) / DX)) - C4 / (1.0 + 2.0 * DX_2 + DY_2) * (q[i][j] - q[i][j - 1]);
      }
      u[i][60 - 1] = 1.0;
    }
  }
}