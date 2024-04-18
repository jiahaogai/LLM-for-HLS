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
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      mul1 = DX_2 * ((double )((int )((+2.0) * DX)));
      mul2 = DY * ((double )((int )((+2.0) * DY)));
      a = -mul1 / 2.0;
      b = 1.0 + a;
      c = mul2 / 2.0;
      d = 1.0 + c;
      tmp = d * ((u[i + 1][j] + u[i - 1][j]) / DX_2) + c * ((v[i][j + 1] + v[i][j - 1]) / DY_2);
      p[i][j] = b * ((u[i][j] + b * tmp) / d) - a * (v[i][j] / d);
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 1; j < 59; j++) {
      mul3 = DX * ((double )((int )((+2.0) * DX)));
      mul4 = DY_2 * ((double )((int )((+2.0) * DY)));
      a = -mul3 / 2.0;
      b = 1.0 + a;
      c = mul4 / 2.0;
      d = 1.0 + c;
      tmp = d * ((v[i + 1][j] + v[i - 1][j]) / DX_4) + c * ((u[i][j + 1] + u[i][j - 1]) / DY_4);
      q[i][j] = b * ((v[i][j] + b * tmp) / d) - a * (u[i][j] / d);
    }
  }
}