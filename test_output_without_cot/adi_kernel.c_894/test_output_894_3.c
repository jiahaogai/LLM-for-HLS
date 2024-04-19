#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  int k;
  int idx;
  int idy;
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
  double tmp;
  double mul;
  
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
  C1 = 3.0 * (DX_5 + DY_5);
  C2 = 4.0 * (DX_4 + DY_4);
  C1_2 = C1 * DX_2;
  C1_3 = C1 * DX_3;
  C1_4 = C1 * DX_4;
  C1_5 = C1 * DX_5;
  C2_2 = C2 * DX_2 * DY_2;
  C2_3 = C2 * DX_3 * DY_2;
  C2_4 = C2 * DX_4 * DY_2;
  C2_5 = C2 * DX_5 * DY_2;
  A1 = 1.0 / (C1 + C2);
  A2 = C1_2 * A1;
  A3 = C1_3 * A1;
  A4 = C1_4 * A1;
  A5 = C1_5 * A1;
  B1 = C2_2 * A1;
  B2 = (C2 + 2.0 * C1) * A1;
  B3 = C2_3 * A1;
  B4 = C2_4 * A1;
  B5 = C2_5 * A1;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_j:
  for (j = 1; j < 59; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_i:
    for (i = 1; i < 59; i++) {
      idx = 60 * j + i;
      v[j][i] = -1.0 / ((double )60) * (u[j][i + 1] - u[j][i - 1]) + v[j][i];
      u[j][i] = 1.0 / ((double )60) * (p[j + 1][i] - p[j - 1][i]) - 1.0 / ((double )360) * (q[j][i + 1] - q[j][i - 1]) + u[j][i];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  loop_t:
  for (t = 1; t <= 390; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_j:
    for (j = 1; j < 59; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      loop_i:
      for (i = 1; i < 59; i++) {
        idx = 60 * j + i;
        mul = DX_5 * u[j][i] + DY_5 * v[j][i] + A1 * p[j][i] + A2 * u[j][i - 2] + A3 * u[j][i - 1] + A4 * u[j][i + 1] + A5 * u[j][i + 2] - B1 * v[j][i - 2] - B2 * v[j][i - 1] - B3 * v[j][i + 1] - B4 * v[j][i + 2];
        tmp = DX_5 * v[j][i] + DY_5 * u[j][i] + A1 * q[j][i] + A2 * v[j - 2][i] + A3 * v[j - 1][i] + A4 * v[j + 1][i] + A5 * v[j + 2][i] - B1 * u[j - 2][i] - B2 * u[j - 1][i] - B3 * u[j + 1][i] - B4 * u[j + 2][i];
        p[j][i] = mul;
        q[j][i] = tmp;
      }
    }
  }
}