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
  loop_tsteps:
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_u:
    for (i = 1; i <= 58; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_v:
      for (j = 1; j <= 58; j++) {
        u[i][j] = ((double )0);
        v[i][j] = ((double )0);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_p:
    for (i = 1; i <= 58; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      loop_q:
      for (j = 1; j <= 58; j++) {
        p[i][j] = (((B1 * (((double ) 2.0) * u[i][j] - u[i - 1][j] - u[i + 1][j])) + (B2 * (((double ) 2.0) * v[i][j] - v[i][j - 1] - v[i][j + 1])))) / ((double ) 2.0);
        q[i][j] = (((B2 * (((double ) 2.0) * u[i][j] - u[i - 1][j] - u[i + 1][j])) + (B1 * (((double ) 2.0) * v[i][j] - v[i][j - 1] - v[i][j + 1])))) / ((double ) 2.0);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    loop_o:
    for (i = 1; i <= 58; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      loop_r:
      for (j = 1; j <= 58; j++) {
        a = ((double )(i - 1));
        b = ((double )(j - 1));
        c = ((double )(i - 1));
        d = ((double )(j + 1));
        u[i][j] = (p[i][j] - (mul1 * (v[a][j] - v[c][j])) + (mul2 * (u[d][b] - u[d][c])));
        v[i][j] = (q[i][j] - (mul1 * (u[a][j] - u[c][j])) + (mul2 * (v[d][b] - v[d][c])));
      }
    }
  }
}