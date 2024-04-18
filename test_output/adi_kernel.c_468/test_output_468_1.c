#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[200][240],double v[200][240],double p[240][200],double q[240][200])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 390; t++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (j = 1; j < 240 - 1; j++) {
        v[i][j] = 1.0 / 4.0 * (u[i - 1][j] - 2.0 * u[i][j] + u[i + 1][j]) + 1.0 / 4.0 * (f[i][j + 1] - f[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 1; j < 240 - 1; j++) {
        u[i][j] = 1.0 / 4.0 * (p[i][j - 1] - 2.0 * p[i][j] + p[i][j + 1]) + 1.0 / 4.0 * (v[i + 1][j] - v[i - 1][j]);
      }
    }
  }
//#pragma endscop
}