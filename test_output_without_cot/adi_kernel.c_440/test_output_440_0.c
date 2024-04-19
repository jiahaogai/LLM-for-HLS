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
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  DY = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DT = 1.0 / ((double )40);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B1 = 2.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B2 = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul1 = B1 * DT / ((DX * DX));
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul2 = B2 * DT / ((DY * DY));
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  a = -mul1 / (mul1 - mul2);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  b = 1.0 + a * mul2;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  c = -a * DX;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  d = DY;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 59; j++) {
        p[i][j] = -c / (b + p[i][j - 1]);
        q[i][j] = (d * u[j][i]) + (1.0 + 2.0 * d) * p[i][j] * q[i][j - 1] + v[j][i];
      }
      v[60][i] = 1.0;
      j = 60;
      u[j][i] = q[i][j] / ((d * u[j][i]) - p[i][j] * q[i][j - 1] - v[j][i]);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 58; j > 0; j--) {
        u[j][i] = q[i][j] / ((d * u[j][i]) - p[i][j] * u[j + 1][i] - v[j][i]);
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 1; j < 59; j++) {
        p[i][j] = -d / (b + p[i][j - 1]);
        q[i][j] = (c * v[j][i]) + (1.0 + 2.0 * c) * p[i][j] * q[i][j - 1] + u[j][i];
      }
      u[i][60] = 1.0;
      j = 60;
      v[j][i] = q[i][j] / ((c * v[j][i]) - p[i][j] * q[i][j - 1] - u[j][i]);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      for (j = 58; j > 0; j--) {
        v[j][i] = q[i][j] / ((c * v[j][i]) - p[i][j] * v[j + 1][i] - u[j][i]);
      }
    }
  }
}