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
//#pragma scop
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DT = 1.0 / ((double )40);
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1 / 2.0;
  b = -mul2 / 2.0;
  c = 1.0 + a;
  d = 1.0 + b;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] + u[i][j - 1] + b * p[i][j + 1] ;
        q[i][j] = -d * q[i][j - 1] + u[i][j - 1] + c * q[i][j + 1] ;
        v[j][i] = -mul1 * p[i][j] + d * v[j][i - 1] + mul2 * q[i][j] ;
      }
      v[60][i] = 1.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] + v[j - 1][i] + b * p[i][j + 1] ;
        q[i][j] = -d * q[i][j - 1] + v[j - 1][i] + c * q[i][j + 1] ;
        u[i][j] = -mul1 * p[i][j] + d * u[i][j - 1] + mul2 * q[i][j] ;
      }
      u[i][60] = 1.0;
    }
  }
//#pragma endscop
}