

 #pragma ACCEL kernel

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
  double x;
  double y;
  double u_x;
  double u_y;
  double v_x;
  double v_y;
  double p_x;
  double p_y;
  double q_x;
  double q_y;
  double rho;
  double tmp;
  double b1;
  double b2;
  double a1;
  double a2;
  double nu;

//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 1; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; ++i) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 59; ++j) {
        DX = ((double )(((int )(((double )60) / ((double )600.0)))));
        DY = ((double )(((int )(((double )60) / ((double )600.0)))));
        DX2 = DX * DX;
        DY2 = DY * DY;
        DXDY = DX * DY;
        C1 = 1.0 / (DX2 + DY2);
        C2 = 1.0 / (2.0 * (1.0 + DX2 + DY2));
        C12 = C1 * C2;
        C1D2 = C1 / D2;
        x = (((int )DX) * i) + 1;
        y = (((int )DY) * j) + 1;
        u_x = (u[i + 1][j] - u[i - 1][j]) / ((double )2 * DX);
        u_y = (u[i][j + 1] - u[i][j - 1]) / ((double )2 * DY);
        v_x = (v[i + 1][j] - v[i - 1][j]) / ((double )2 * DX);
        v_y = (v[i][j + 1] - v[i][j - 1]) / ((double )2 * DY);
        p_x = ((-1.0 * (u_x * u[i][j] - u_y * v[i][j]) + q[i][j]) / ((double )C12 * rho[i][j]) - (u[i][j] * (p[i + 1][j] - p[i - 1][j])) / ((double )2.0 * DX2) + (v[i][j] * (p[i][j + 1] - p[i][j - 1])) / ((double )2.0 * DY2)) + (((((float ) 1.0) / (((float ) 4.0) * DX2)) * (u[i + 1][j + 1] - u[i + 1][j - 1] - u[i - 1][j + 1] + u[i - 1][j - 1])) + (((float ) 1.0) / (((float ) 4.0) * DY2) * (v[i + 1][j + 1] - v[i - 1][j + 1] - v[i + 1][j - 1] - v[i - 1][j - 1]))) * (p[i][j + 1] - p[i][j - 1] - p[i - 1][j] + p[i + 1][j])) / (((double )2) * (1.0 + u_x * ((double )2.0) * DX + v_x * ((double )2.0) * DY));
        p_y = ((-1.0 * (u_x * v[i][j] - u_y * u[i][j]) + q[i][j]) / ((double )C12 * rho[i][j]) - (u[i][j] * (p[i + 1][j] - p[i - 1][j])) / ((double )2.0 * DX2) + (v[i][j] * (p[i][j + 1] - p[i][j - 1])) / ((double )2.0 * DY2)) + (((((float ) 1.0) / (((float ) 4.0) * DX2)) * (v[i + 1][j + 1] - v[i + 1][j - 1] - v[i - 1][j + 1] + v[i - 1][j - 1])) + (((float ) 1.0) / (((float ) 4.0) * DY2) * (u[i + 1][j + 1] - u[i - 1][j + 1] - u[i + 1][j - 1] - u[i - 1][j - 1]))) * (p[i + 1][j] - p[i - 1][j] - p[i][j + 1] + p[i][j - 1])) / (((double )2) * (1.0 + u_x * ((double )2.0) * DX + v_x * ((double )2.0) * DY));
        q_x = -1.0 * (u_x * p[i][j] - v_x * ((double )q[i][j]) + ((double )2.0) * (u_x * u_x * u[i][j] + v_x * v_x * v[i][j] - ((double )2.0) * u_x * v_x * (u[i][j] + v[i][j])) / (1.0 + u_x * ((double )2.0) * DX + v_x * ((double )2.0) * DY)) / (DX2 + ((double )2.0) * DX * DY + DY2);
        q_y = -1.0 * (u_y * p[i][j] - v_y * ((double )q[i][j]) + ((double )2.0) * (u_y * u_y * u[i][j] + v_y * v_y * v[i][j] - ((double )2.0) * u_y * v_y * (u[i][j] + v[i][j])) / (1.0 + u_x * ((double )2.0) * DX + v_x * ((double )2.0) * DY)) / (DX2 + ((double )2.0) * DX * DY + DY2);
        tmp = - 1.0 * (u_x * u_y * (u[i][j] - ((double )2.0) * (u[i][j] + v[i][j]) / ((double )3.0) + v[i][j]) + v_x * v_y * (v[i][j] - ((double )2.0) * (v[i][j] + u[i][j]) / ((double )3.0) + u[i][j])) / (1.0 + u_x * ((double )2.0) * DX + v_x * ((double )2.0) * DY);
        b1 = p_x - tmp * v_y;
