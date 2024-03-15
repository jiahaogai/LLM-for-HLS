
- #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DX2;
  double DY2;
  double DXDY;
  double C1;
  double C2;
  double C12;
  double C1D2;
  double ND;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//#pragma scop
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 1; j < 59; j++) {
        DX = ((((float )60)) - (((float )59)));
        DY = ((((float )60)) - (((float )59)));
        DX2 = (DX * DX);
        DY2 = (DY * DY);
        DXDY = (DX * DY);
        C1 = ((-2.0) * DX2 / (DX2 + DY2));
        C2 = ((-2.0) * DY2 / (DX2 + DY2));
        C12 = (C1 * C2);
        C1D2 = (C1 * DY2);
        ND = (1.0 + C12 + C1D2);
        u[i][j] = ((((-1.0) * ((((float )4.0) * (u[i - 1][j] - 2.0 * u[i][j] + u[i + 1][j])) + (v[i][j - 1] - 2.0 * v[i][j] + v[i][j + 1]))) / ND) + (p[i][j]));
        v[i][j] = ((((-1.0) * ((((float )4.0) * (v[i - 1][j] - 2.0 * v[i][j] + v[i + 1][j])) + (u[i][j - 1] - 2.0 * u[i][j] + u[i][j + 1]))) / ND) + (q[i][j]));
      }
    }
//#pragma endscop
  }
}
