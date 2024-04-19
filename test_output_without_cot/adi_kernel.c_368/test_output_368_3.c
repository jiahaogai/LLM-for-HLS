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
  double DX_3;
  double DY_3;
  double DX_4;
  double DY_4;
  double DX_5;
  double DY_5;
  double C1;
  double C2;
  double C1_2;
  double C1_3;
  double C1_4;
  double C1_5;
  double C2_2;
  double C2_3;
  double C2_4;
  double C2_5;
  double A1;
  double A2;
  double A3;
  double A4;
  double A5;
  double B1;
  double B2;
  double B3;
  double B4;
  double B5;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_3 = DX_2 * DX;
  DY_3 = DY_2 * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_5 = DX_2 * DX_3;
  DY_5 = DY_2 * DY_3;
  C1 = 3.0 * DX_5 * DY - 4.0 * DX_4 * DY_2 + 5.0 * DX_3 * DY_3 - 4.0 * DX_2 * DY_4 - DX * DY_5;
  C2 = 4.0 * DX_4 * DY - 5.0 * DX_3 * DY_2 + 6.0 * DX_2 * DY_3 - 4.0 * DX_DY_4;
  C1_2 = C1 * DX_2;
  C1_3 = C1 * DX_3;
  C1_4 = C1 * DX_4;
  C1_5 = C1 * DX_5;
  C2_2 = C2 * DY_2;
  C2_3 = C2 * DY_3;
  C2_4 = C2 * DY_4;
  C2_5 = C2 * DY_5;
  A1 = 1.0 / C1;
  A2 = 1.0 / (C1 + C2);
  A3 = 1.0 / (2.0 * C2);
  A4 = 1.0 / (2.0 * (C1 - 2.0 * C2) + C2);
  A5 = 1.0 / (2.0 * (C1 - C2));
  B1 = -(u[0][0] - 2.0 * (u[0][1] + u[1][0]) + u[2][0]) / C1_5 + (v[0][0] - 2.0 * (v[0][1] + v[1][0]) + v[2][0]) / C2_5;
  B2 = -(u[0][0] - 2.0 * (u[0][1] + u[1][1]) + u[2][1]) / C1_4 + (v[0][0] - 2.0 * (v[0][1] + v[1][1]) + v[2][1]) / C2_4;
  B3 = -(u[0][0] - 2.0 * (u[0][1] + u[1][2]) + u[2][2]) / C1_3 + (v[0][0] - 2.0 * (v[0][1] + v[1][2]) + v[2][2]) / C2_3;
  B4 = -(u[0][0] - 2.0 * (u[0][1] + u[1][30]) + u[2][30]) / C1_2 + (v[0][0] - 2.0 * (v[0][1] + v[1][30]) + v[2][30]) / C2_2;
  B5 = -(u[0][0] - 2.0 * (u[0][1] + u[1][58]) + u[2][58]) / C1 + (v[0][0] - 2.0 * (v[0][1] + v[1][58]) + v[2][58]) / C2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 58; i++) {
      v[0][i] = A1 * (p[0][i] - 2.0 * (p[0][i] - q[0][i]) * DX - q[0][i] + q[2][i] - 2.0 * (q[0][i] - q[1][i]) * DX + q[1][i]) + B1 * (u[0][i + 1] - u[0][i - 1]);
      v[30][i] = A1 * (p[30][i] - 2.0 * (p[30][i] - q[30][i]) * DX - q[30][i] + q[32][i] - 2.0 * (q[30][i] - q[31][i]) * DX + q[31][i]) + B1 * (u[30][i + 1] - u[30][i - 1]);
      v[58][i] = A1 * (p[58][i] - 2.0 * (p[58][i] - q[58][i]) * DX - q[58][i] + q[56][i] - 2.0 * (q[58][i] - q[57][i]) * DX + q[57][i]) + B1 * (u[58][i + 1] - u[58][i - 1]);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 30; j++) {
        v[j][i] = A2 * (p[j][i] - 2.0 * (p[j][i] - q[j][i]) * DX - q[j][i] + q[j][i + 1] - 2.0 * (q[j][i] - q[j][i + 1]) * DX + q[j][i + 1]) + A3 * (v[j + 1][i] - v[j - 1][i]) + A4 * (v[j][i + 1] - v[j][i - 1]) + B2 * (u[j][i + 1] - u[j][i - 1]) + B3 * (u[j