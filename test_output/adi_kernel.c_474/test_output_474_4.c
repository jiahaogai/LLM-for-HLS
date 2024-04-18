#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[64][64],double v[64][64],double p[64][64],double q[64][64])
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
  B2 = 1.0;
  mul1 = B1 * DX * DX;
  mul2 = B2 * DY * DY;
  a = -mul1 / (mul1 + mul2);
  b = -mul2 / (mul1 + mul2);
  c = 1.0 + 2.0 * mul1 / (mul1 - mul2);
  d = 1.0 + 2.0 * mul2 / (mul1 - mul2);
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 32; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 63; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 63; j++) {
        p[i][j] = -a * p[i][j - 1] + u[i][j];
        q[i][j] = -b * q[i][j - 1] + v[i][j];
      }
      v[63][i] = 1.0;
      d[i] = a * p[i][62] + b * q[i][62] + c;
      u[i][63] = 1.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 63; i++) {
      u[i][0] = 0.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 63; j++) {
        p[i][j] = -d[j] * p[i][j] + u[i][j];
        q[i][j] = -d[j] * q[i][j] + v[i][j];
      }
      u[i][63] = 0.0;
    }
  }
}