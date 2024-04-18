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
    loop_j:
    for (j = 1; j <= 58; j++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_i:
      for (i = 1; i <= 58; i++) {
        DX = (((double )i) - 30.0);
        DY = (((double )j) - 30.0);
        mul1 = DY * ((2.0 * v[j][i]) - (2.0 * v[j][i - 1]));
        mul2 = DX * (p[j][i] - p[j][i - 1]);
        a = mul1 + mul2;
        b = mul1 - mul2;
        c = DX * ((2.0 * u[j][i]) - (2.0 * u[j][i - 1]));
        d = DY * (q[j][i] - q[j - 1][i]);
        u[j][i] = a + c;
        v[j][i] = b + d;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
    loop_update:
    for (j = 0; j <= 58; j++) {
      for (i = 0; i <= 58; i++) {
        p[j][i] = ((double )((long )0));
        q[j][i] = 0.0;
      }
    }
  }
}