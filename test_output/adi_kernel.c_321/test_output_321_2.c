#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[200][240],double v[200][240],double p[200][240],double q[200][240])
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
  DX = 1.0;
  DY = 1.0;
  DT = 1.0;
  B1 = 2.0;
  B2 = 1.2;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  
#pragma ACCEL PIPELINE auto{off}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 200 - 2; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 240 - 2; j++) {
        a = -mul1 * (u[i][j + 2] - 2.0 * u[i][j + 1] + u[i][j - 0]);
        b = 1.0 + 2.0 * mul2 * (v[i + 2][j] - 2.0 * v[i + 1][j] + v[i - 0][j]);
        c = u[i][j + 2] - 2.0 * u[i][j + 1] + u[i][j - 0];
        d = v[i + 2][j] - 2.0 * v[i + 1][j] + v[i - 0][j];
        p[i][j] = a * b;
        q[i][j] = -c * d;
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 200 - 2; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 240 - 2; j++) {
        a = -mul1 * (v[i + 2][j] - 2.0 * v[i + 1][j] + v[i - 0][j]);
        b = 1.0 + 2.0 * mul2 * (u[i + 2][j] - 2.0 * u[i + 1][j] + u[i - 0][j]);
        c = v[i + 2][j] - 2.0 * v[i + 1][j] + v[i - 0][j];
        d = u[i + 2][j] - 2.0 * u[i + 1][j] + u[i - 0][j];
        p[i][j] = a * b;
        q[i][j] = -c * d;
      }
    }
  }
}