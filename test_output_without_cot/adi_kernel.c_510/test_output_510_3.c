#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[20][24][60],double v[20][24][60],double p[20][25][60],double q[20][25][60])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 20; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 24 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 1; j < 25 - 1; j++) {
        v[t][i][j] = -0.5 * (u[t][i + 1][j] - u[t][i - 1][j]) + 0.5 * (q[t][i + 1][j] - q[t][i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (i = 1; i < 24 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      for (j = 1; j < 25 - 1; j++) {
        u[t][i][j] = -0.5 * (v[t][i][j + 1] - v[t][i][j - 1]) + 0.5 * (p[t][i + 1][j] - p[t][i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (i = 1; i < 24 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      for (j = 1; j < 25 - 1; j++) {
        p[t][i][j] = -0.5 * (u[t][i][j + 1] - u[t][i][j - 1]) + 0.5 * (q[t][i + 1][j] - q[t][i - 1][j]) + 1.0 * (p[t][i + 1][j] - p[t][i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
    for (i = 1; i < 24 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      for (j = 1; j < 25 - 1; j++) {
        q[t][i][j] = -0.5 * (v[t][i + 1][j] - v[t][i - 1][j]) + 0.5 * (p[t][i + 1][j] - p[t][i - 1][j]) + 1.0 * (q[t][i + 1][j] - q[t][i - 1][j]);
      }
    }
  }
//#pragma endscop
}