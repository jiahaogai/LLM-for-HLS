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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 1; j < 240 - 1; j++) {
        v[i][j] = 1.0 / 4.0 * (u[i][j + 1] - u[i][j - 1] + (u[i + 1][j] - u[i - 1][j]));
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      for (j = 1; j < 240 - 1; j++) {
        p[j][i] = 1.0 / 4.0 * (v[i][j] - v[i][j - 1].fl + v[i][j + 1] - v[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L9}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
      for (j = 1; j < 240 - 1; j++) {
        q[i][j] = 1.0 / 4.0 * (p[j][i] - p[j - 1][i] + p[j + 1][i] - p[j][i - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 200 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L12}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
      for (j = 1; j < 240 - 1; j++) {
        u[i][j] = u[i][j] + 1.0 / 40.0 * (p[i + 1][j + 1] - p[i + 1][j - 1] - p[i - 1][j + 1] + p[i - 1][j - 1] - q[i + 1][j + 1] + q[i + 1][j - 1] - q[i - 1][j + 1] + q[i - 1][j - 1]);
      }
    }
  }
//#pragma endscop
}