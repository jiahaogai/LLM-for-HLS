
 #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DT;
  double B1;
  double B2;
  double a;
  double mu;
  double la;
  double bpp;
  double bqq;
  double bpq;
  double expt;
  
#pragma ACCEL PIPELINE auto{off}
  DX = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  DY = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  DT = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  B1 = 2.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  B2 = 1.0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  a = -(B1 + B2);
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  mu = B1 - B2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  la = B2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L8}
  bpp = 2.0 * DT * DX * DX;
  
#pragma ACCEL PIPELINE auto{__PIPE__L9}
  bqq = 2.0 * DT * DY * DY;
  
#pragma ACCEL PIPELINE auto{__PIPE__L10}
  bpq = 2.0 * DT * DX * DY;
  
//Column Sweep
  for (t = 1; t <= 40; t++) {
// Row Sweep
    for (i = 1; i < 58; i++) {
      expt = exp(-la * DT);
      v[0][i] = ((B2 * u[0][i]) + ((1.0 - B1 - B2) * u[1][i]) + (B1 * u[2][i]));
      p[i][0] = 0.0;
      q[i][0] = ((v[0][i] - u[0][i]) / DX);
      q[i][0] -= ((p[i][1] - p[i][0]) / DY);
      q[i][0] = ((q[i][0]) * expt);
      
#pragma ACCEL PIPELINE auto{__PIPE__L11}
      
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{__PARA__L1}
      for (j = 1; j < 58; j++) {
        v[i][j] = ((B2 * u[i][j]) + ((1.0 - B1 - B2) * u[i][j] + u[i][j - 1]) + (B1 * u[i][j + 1])) - ((DX * DX) * p[i][j] + (DY * DY) * q[i][j] + 2.0 * DX * DY * p[i][j + 1] * q[i][j]);
        p[i][j] =  - ((DX * DX) * inv_sqr_DX) * (a * p[i][j] + bpp * v[i][j]) + ((1.0 - 2.0 * a) * p[i][j] + (1.0 + 4.0 * bpp) * v[i][j] - expt * p[i][j + 1]));
        q[i][j] =  - ((DY * DY) * inv_sqr_DY) * (a * q[i][j] + bqq * v[i][j]) + ((1.0 - 2.0 * a) * q[i][j] + (1.0 + 4.0 * bqq) * v[i][j] - expt * q[i][j + 1]) - DX * (p[i][j + 1] - p[i][j]) / DY;
      }
    }
// Row Sweep
    for (i = 57; 0 < i; i--) {
      expt = exp(-la * DT);
      u[0][i] = v[i][0];
      q[i][0] = 0.0;
      p[i][0] = ((v[i][0] - u[i][0]) / DY) - (DX * DX * p[i][1] / DY) + ((1.0 - 2.0 * a) * p[i][0] + (1.0 + 4.0 * bpp) * v[i][0] - expt * p[i][1]);
      p[i][0] /= (- 2.0 * a * DX * DX);
      
#pragma ACCEL PIPELINE auto{__PIPE__L12}
      
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L2}
      for (j = 1; j < 58; j++) {
        u[i][j] = v[i][j] - DX * (p[i][j] - p[i][j - 1]) / DX - DY * (q[i][j] - q[i][j - 1]) / DY;
        q[i][j] =  - ((DX * DX) * inv_sqr_DX) * (a * q[i][j] + bqq * u[i][j]) + ((1.0 - 2.0 * a) * q[i][j] + (1.0 + 4.0 * bqq) * u[i][j] - expt * q[i][j + 1]) - (DY * DY) * p[i][j] / DX;
      }
    }
  }
}
