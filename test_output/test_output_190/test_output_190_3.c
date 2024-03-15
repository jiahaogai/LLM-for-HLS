

  int tsteps;
  int d;
  int n;
  double u[60][60];
  double v[60][60];
  double p[60][60];
  double q[60][60];
  double r[60][60];
  double s[60][60];
  double pad[60][60];

#pragma ACCEL kernel

void kernel_heat_3d(int tsteps,int n,double A[60][60],double B[60][60])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 1; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        s[i][j] = 2.0 * A[i][j] - 1.0 * q[i][j] - 1.0 * p[i][j] - 1.0 * r[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 59; j++) {
        p[i][j] = 1.0 * A[i][j] - 1.0 * u[i][j] - 1.0 * s[i][j] - 1.0 * v[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        q[i][j] = 1.0 * B[i][j] - 1.0 * p[i][j] - 1.0 * u[i][j] - 1.0 * v[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 59; j++) {
        v[i][j] = 1.0 * s[i][j] - 1.0 * q[i][j] - 1.0 * p[i][j] - 1.0 * u[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        u[i][j] = 1.0 * r[i][j] - 1.0 * v[i][j] - 1.0 * q[i][j] - 1.0 * p[i][j];
      }
    }
  }
//#pragma endscop
}
