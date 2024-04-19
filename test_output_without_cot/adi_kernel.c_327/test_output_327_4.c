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
  C1 = 3.0 * (DX_5 + DY_5);
  C2 = 3.0 * (2.0 * DX_5 - DY_5);
  C1_2 = 3.0 * DX_2 * DX_4;
  C1_3 = 3.0 * DX_3 * DX_4;
  C1_4 = 3.0 * DX_4 * DX_4;
  C1_5 = 3.0 * DX_5 * DX_4;
  C2_2 = 3.0 * DY_2 * DY_4;
  C2_3 = 3.0 * DY_3 * DY_4;
  C2_4 = 3.0 * DY_4 * DY_4;
  C2_5 = 3.0 * DY_5 * DY_4;
  A1 = 2.0 * (DX_5 + DY_5) - C2;
  A2 = DX_5 - DY_5 + 2.0 * (C1 - C2);
  A3 = DX_5 - DY_5 + C2_2;
  A4 = DX_5 - DY_5 + 2.0 * (C1_2 - C2_2);
  A5 = 2.0 * (DX_5 - DY_5) + C2;
  B1 = -2.0 * (DX_5 + DY_5) + C2;
  B2 = DX_5 - DY_5 - 2.0 * (C1 + C2);
  B3 = DX_5 - DY_5 + C2_2;
  B4 = DX_5 - DY_5 - 2.0 * (C1_2 + C2_2);
  B5 = 2.0 * (DX_5 + DY_5) + C2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 390; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        double sum_A1_A2_A3_A4_A5;
        double sum_B1_B2_B3_B4_B5;
        double p_tmp;
        double q_tmp;
        double u_tmp;
        double v_tmp;
        sum_A1_A2_A3_A4_A5 = A1 * p[i][j - 1] + A2 * p[i][j] + A3 * p[i][j + 1] + A4 * p[i][j + 2] + A5 * p[i][j + 3];
        sum_B1_B2_B3_B4_B5 = B1 * q[i - 1][j] + B2 * q[i][j] + B3 * q[i + 1][j] + B4 * q[i + 2][j] + B5 * q[i + 3][j];
        p_tmp = - sum_A1_A2_A3_A4_A5 + sum_B1_B2_B3_B4_B5;
        u_tmp = u[i][j] - DX * DX * p_tmp - DY * DY * q_tmp;
        q_tmp = q[i][j] - DX * DY * p_tmp - DY * DX * u_tmp;
        p[i][j] = p_tmp;
        q[i][j] = q_tmp;
        v_tmp = DX * ( + 3.0 * u_tmp - 2.0 * q_tmp) - 2.0 * DY * v_tmp;
        v[i][j] = v_tmp;
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 58; i >= 1; --i) {
      v[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 59; j++) {
        double sum_A1_A2_A3_A4_A5;
        double sum_B1_B2_B3_B4_B5;
        double p_tmp;
        double q_tmp;
        double u_tmp;
        double v_tmp;
        sum_A1_A2_A3_A4_A5 = A1 * p[i][j - 1] + A2 * p[i][j] + A3 * p[i][j + 1] + A4 * p[i][j + 2] + A5 * p[i][j + 3];
        sum_B1_B2_B3_B4_B5 = B1 * q[i - 1][j] + B2 * q[i][j