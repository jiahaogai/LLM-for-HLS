#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][80],double v[60][80],double p[60][80],double q[60][80])
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
  DX = 1.0;
  
#pragma ACCEL TILE FACTOR=auto{1}
  DY = 1.0;
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DT = 1.0;
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1;
  b = 2.0 - mul2;
  c = mul1;
  d = -mul2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 79; j++) {
        p[i][j] = -a / (a * p[i][j - 1] + b) * u[i][j - 1] + u[i][j];
        q[i][j] = -c / (c * q[i][j - 1] + d) * v[j - 1][i] + v[j][i];
      }
      v[69][i] = 1.0;
      u[i][78] = p[i][78];
      j = 78;
      i = 69;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 79; j++) {
        p[i][j] = -a / (a * p[i][j - 1] + b) * u[i][j - 1] + u[i][j];
        q[i][j] = -c / (c * q[i][j - 1] + d) * v[j - 1][i] + v[j][i];
      }
      u[i][78] = 1.0;
      v[i][78] = p[i][78];
      j = 78;
      i = 58;
    }
  }
}