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
  DX = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  DY = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DT = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B1 = 2.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  B2 = 1.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul1 = B1 * DT / ((DX * DX) + (DY * DY));
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  mul2 = B2 * DT / ((DX * DX) + (DY * DY));
  
// Column Sweep
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 1; j < 59; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      a = -mul1 * (u[i - 1][j] - 2.0 * u[i][j] + u[i + 1][j]);
      b = -mul1 * (v[i][j - 1] - 2.0 * v[i][j] + v[i][j + 1]);
      c = 1.0 + (mul2 * ((u[i - 1][j] - 2.0 * u[i][j] + u[i + 1][j]) / (DX * DX)) - (2.0 * v[i][j - 1] - 2.0 * v[i][j] + v[i][j + 1]) / (DY * DY));
      d = u[i][j] - (a - b) / c;
      p[i][j] = d;
      q[i][j] = ((v[i][j] - d) - b) / a;
    }
  }
// Row Sweep
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        v[i][j] =  - 1.0 * (p[i][j] - v[i][j] - (q[i][j] * (u[i][j] - u[i][j - 1])));
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        u[i][j] = p[i][j] - v[i][j] ;
      }
    }
  }
}