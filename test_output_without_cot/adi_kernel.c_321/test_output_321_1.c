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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  DX = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  DY = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  DT = 1.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  B1 = 2.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  B2 = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  mul1 = B1 * DX * DX;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  mul2 = B2 * DY * DY;
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  a = -mul1 / ((mul1 + mul2));
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
  b = -mul2 / ((mul1 + mul2));
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
  c = 1.0 + ((2.0 * mul1) / ((mul1 + mul2)));
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
  d = 1.0 + ((2.0 * mul2) / ((mul1 + mul2)));
  
#pragma ACCEL PIPELINE auto{__PIPE__L12}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
  
#pragma ACCEL PIPELINE auto{__PIPE__L13}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L13}
  for (t = 1; t <= 39; t++) {
// Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L14}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L14}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L15}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * (p[i][j - 1] + p[i][j + 1]) - b * (q[i][j - 1] + q[i][j + 1]) + u[i][j];
        q[i][j] = -d * (q[i][j - 1] + q[i][j + 1]) + c * (p[i][j - 1] + p[i][j + 1]) + v[i][j];
        v[i][j] = d * (u[i][j - 1] + u[i][j + 1]) - (a + c) * v[i][j] + q[i][j];
      }
      v[60 - 1][i] = 1.0;
    }
// Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L16}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L16}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L17}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L18}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * (p[i - 1][j] + p[i + 1][j]) - b * (q[i - 1][j] + q[i + 1][j]) + u[i][j];
        q[i][j] = -d * (q[i - 1][j] + q[i + 1][j]) + c * (p[i - 1][j] + p[i + 1][j]) + v[i][j];
        u[i][j] = d * (p[i - 1][j] + p[i + 1][j]) - (a + c) * u[i][j] + q[i][j];
      }
      u[i][60 - 1] = 1.0;
    }
  }
}