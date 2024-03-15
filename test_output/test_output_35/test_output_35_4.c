
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
  double C1;
  double C2;
  double C1_2;
  double C1_4;
  double C1_6;
  double N1;
  double N2;
  double N3;
  double N4;
  double N5;
  double N6;
  double M1;
  double M2;
  double M3;
  double M4;
  double M5;
  double M6;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double mul5;
  double mul6;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DX_2 = DX * 2.0;
  DY_2 = DY * 2.0;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  C1 = 3.0 * (DX_2 * DY_2) - DX_4 * DY_2;
  C2 = 3.0 * (DX_2 * DY_4) - DX_4 * DY_4;
  C1_2 = C1 * 2.0;
  C1_4 = C1 * 4.0;
  C1_6 = C1 * 6.0;
  N1 = -1.0 / (DX_2 * DY);
  N2 = 1.0 / (2.0 * DX_2 * DY);
  N3 = -1.0 / (2.0 * DX_4 * DY);
  N4 = 1.0 / (4.0 * DX_4 * DY);
  N5 = -1.0 / (2.0 * DX_6 * DY);
  N6 = 1.0 / (6.0 * DX_6 * DY);
  M1 = 1.0 / (2.0 * DX_2 * DY_2);
  M2 = -1.0 / (2.0 * DX * DY_2);
  M3 = 1.0 / (2.0 * DX_2 * DY_4);
  M4 = 1.0 / (4.0 * DX_4 * DY_2);
  M5 = -1.0 / (2.0 * DX_4 * DY_4);
  M6 = 1.0 / (4.0 * DX_6 * DY_2);
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
      DX_2 = DX * ((double )(60 - 2 * 1));
      DY_2 = DY * ((double )(60 - 2 * 1));
      DX_4 = DX_2 * DX_2;
      DY_4 = DY_2 * DY_2;
      DX_6 = DX_4 * DX_2;
      DY_6 = DY_4 * DY_2;
      C1 = 3.0 * (DX_2 * DY_2) - DX_4 * DY_2;
      C2 = 3.0 * (DX_2 * DY_4) - DX_4 * DY_4;
      C1_2 = C1 * ((double )2);
      C1_4 = C1 * ((double )4);
      C1_6 = C1 * ((double )6);
      N1 = -1.0 / (((double )2) * DX_2 * DY);
      N2 = 1.0 / (((double )2) * DX_2 * DY);
      N3 = -1.0 / (((double )4) * DX_4 * DY);
      N4 = 1.0 / (((double )4) * DX_4 * DY);
      N5 = -1.0 / (((double )6) * DX_6 * DY);
      N6 = 1.0 / (((double )6) * DX_6 * DY);
      M1 = 1.0 / (((double )2) * DX_2 * DY_2);
      M2 = -1.0 / (((double )2) * DX * DY_2);
      M3 = 1.0 / (((double )2) * DX_2 * DY_4);
      M4 = 1.0 / (((double )4) * DX_4 * DY_2);
      M5 = -1.0 / (((double )4) * DX_4 * DY_4);
      M6 = 1.0 / (((double )4) * DX_6 * DY_2);
      a = ((((N1 * (S2(i + 1, j) - S2(i - 1, j)) - N4 * (S4(i + 1, j) - S4(i - 1, j))) - N5 * (S6(i + 1, j) - S6(i - 1, j))) - N6 * (S8(i + 1, j) - S8(i - 1, j))) - (M2 * u2(i, j + 1) - M2 * u2(i, j - 1)));
      b = ((((N2 * (S2(i + 1, j + 1) - S2(i - 1, j + 1)) - N4 * (S4(i + 1, j + 1) - S4(i - 1, j + 1))) - N5 * (S6(i + 1, j + 1) - S6(i - 1, j + 1))) - N6 * (S8(i + 1, j + 1) - S8(i - 1, j + 1))) - (M3 * u2(i, j + 2) - M3 * u2(i, j - 2)));
      c = ((((N3 * (S2(i + 2, j) - S2(i - 2, j)) - N4 * (S4(i + 2, j) - S4(i - 2, j))) - N5 * (S6(i + 2, j) - S6(i - 2, j))) - N6 * (S8(i + 2, j) - S8(i - 2, j))) - (M4 * u2(i, j + 1) - M4 * u2(i, j - 1)));
      d = ((((N1 * (S4(i + 1, j) - S4(i - 1, j)) - N3 * (S6(i + 1, j) - S6(i - 1, j))) - N5 * (S8(i + 1, j) - S8(i - 1