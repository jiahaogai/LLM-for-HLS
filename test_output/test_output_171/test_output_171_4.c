

 #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60],double r[60][60],double s[60][60])
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
  double C22;
  double del;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;

//#pragma scop
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DX2 = DX * DX;
  DY2 = DY * DY;
  DXDY = DX * DY;
  C1 = 3.0 * DX2 * DY2;
  C2 = 3.0 * DX2 - 2.0 * DXDY * DY2;
  C12 = C1 * C2;
  C22 = C2 * C2;
  del = 1.0 / 41.0;
  mul1 = -1.0 * del * DXDY * C22;
  mul2 = 1.0 - 2.0 * del * DY2 * C2 + del * C22;
  a = 1.0 + (mul1 + mul2);
  b = DXDY * (C1 - 2.0 * C2) + mul2;
  c = DX2 * (C1 - C2) + (1.0 - 2.0 * del) * DX2 * C22;
  d = DY2 * C12;
  e = -1.0 - (mul1 + mul2);
  f = DXDY * (C12 - 2.0 * C22) + mul1;
// First tsteps loop
  for (t = 0; t <= 39; t++) {
// Four nested parallelized loops
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// A = Dx2*Dy2
	u[i][j] = a * (*(u + (i - 1) * 60) + *(u + (i + 1) * 60) + *(u + (j - 1) * 60) + *(u + (j + 1) * 60)) + b * (*(u + (i - 1) * 60) - *(u + (i + 1) * 60) - *(u + (j - 1) * 60) + *(u + (j + 1) * 60)) + c * (*(u + (i - 1) * 60) + *(u + (i + 1) * 60) - 2.0 * (*(u + (j - 1) * 60) + *(u + (j + 1) * 60))) + d * (*(u + (j - 1) * 60));
      }
    }
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// B = Dy2*Dx2
	v[i][j] = e * (*(v + (i - 1) * 60) + *(v + (i + 1) * 60) + *(v + (j - 1) * 60) + *(v + (j + 1) * 60)) + f * (*(v + (i - 1) * 60) - *(v + (i + 1) * 60) - *(v + (j - 1) * 60) + *(v + (j + 1) * 60)) + c * (*(v + (i - 1) * 60) + *(v + (i + 1) * 60) - 2.0 * (*(v + (j - 1) * 60) + *(v + (j + 1) * 60))) + d * (*(v + (j - 1) * 60));
      }
    }
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// C = B + Dx(A - q)
	p[i][j] = b * (*(p + (i - 1) * 60) + *(p + (i + 1) * 60) + *(p + (j - 1) * 60) + *(p + (j + 1) * 60)) + f * (*(p + (i - 1) * 60) - *(p + (i + 1) * 60) - *(p + (j - 1) * 60) + *(p + (j + 1) * 60)) + c * (*(p + (i - 1) * 60) + *(p + (i + 1) * 60) - 2.0 * (*(p + (j - 1) * 60) + *(p + (j + 1) * 60))) + d * (*(p + (j - 1) * 60)) - (*(u + (i - 1) * 60) - q[i][j]);
      }
    }
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// D = Dx(A - r)
	q[i][j] = a * (*(q + (i - 1) * 60) + *(q + (i + 1) * 60) + *(q + (j - 1) * 60) + *(q + (j + 1) * 60)) + c * (*(q + (i - 1) * 60) + *(q + (i + 1) * 60) - 2.0 * (*(q + (j - 1) * 60) + *(q + (j + 1) * 60))) + d * (*(q + (i - 1) * 60)) - (*(u + (i - 1) * 60) - r[i][j]);
      }
    }
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// S = Dy(A - p)
	s[i][j] = a * (*(s + (i - 1) * 60) + *(s + (i + 1) * 60) + *(s + (j - 1) * 60) + *(s + (j + 1) * 60)) + d * (*(s + (j - 1) * 60)) - (*(v + (i - 1) * 60) - p[i][j]);
      }
    }
    for (i = 1; i <= 38; i++) {
      for (j = 1; j <= 38; j++) {
// P = Dy(B - s)
	p[i][j] = b * (*(p + (i - 1) * 60) + *(p + (i + 1) * 60) + *(p + (j - 1) * 60) + *(p + (j + 1) * 60)) + d * (*(p + (j - 1) * 60)) - (*(v + (i - 1) * 60) - s[i][j]);
      }
    }
  }
//#pragma endscop
}
