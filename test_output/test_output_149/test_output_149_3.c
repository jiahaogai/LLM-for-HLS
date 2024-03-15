
 #pragma ACCEL kernel

void kernel_big(int tsteps,int n,double u[60][80],double v[60][80],double w[60][80],double x[60][80],double y[60][80],double z[60][80])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 0; j <= 79;j++) {
        v[i][j] = u[i][j] - 0.5 * (x[i][j] - ((u[i][j] * y[i][j]) / z[i][j]));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j <= 79;j++) {
        w[i][j] = v[i][j] - 0.5 * (y[i][j] - ((v[i][j] * x[i][j]) / z[i][j])) - 1.0 / (240.0) * (6.0 * u[i][j] - 8.0 * u[i][j - 1] - 8.0 * u[i][1 + j] - u[i][j + 1] + 5.0 * v[i][j - 1] - 5.0 * v[i][1 + j] + v[i][j + 1] - 1.0 / (sqrt(6.28)) * (sin(z[i][j]) - sin(z[i][j - 1])));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j <= 79;j++) {
        x[i][j] = w[i][j] - 0.5 * (v[i][j] - 1.0 / (240.0) * (6.0 * w[i][j] - 8.0 * w[i][j - 1] - 8.0 * w[i][1 + j] - w[i][j + 1] + 5.0 * u[i][j] - 5.0 * u[i][j - 1] + u[i][j + 1] - 1.0 / (sqrt(6.28)) * (cos(z[i][j]) - cos(z[i][j - 1]))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      for (j = 0; j <= 79;j++) {
        y[i][j] = x[i][j] - 0.5 * (u[i][j] - 1.0 / (240.0) * (6.0 * x[i][j] - 8.0 * x[i][j - 1] - 8.0 * x[i][1 + j] - x[i][j + 1] + 5.0 * w[i][j] - 5.0 * w[i][j - 1] + w[i][j + 1] - 1.0 / (sqrt(6.28)) * (sin(z[i][j]) - sin(z[i][j - 1]))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L10}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
      for (j = 0; j <= 79;j++) {
        z[i][j] = y[i][j] - (1.0 / 720.0) * (x[i][j] - 2.0 * y[i][j] + x[i][j - 1] + x[i][1 + j] - 2.0 * y[i][j - 1] + y[i][1 + j] - x[i - 1][j] - 2.0 * x[i - 1][j] + x[i - 1][j - 1] - 2.0 * y[i - 1][j - 1] + y[i - 1][j - 1] - x[i - 1][j + 1] - 2.0 * y[i - 1][j + 1] + y[i - 1][j + 1] - x[i + 1][j] - 2.0 * x[i + 1][j] + x[i + 1][j - 1] - 2.0 * y[i + 1][j - 1] + y[i + 1][j - 1] - x[i + 1][j + 1] - 2.0 * y[i + 1][j + 1] + y[i + 1][j + 1]);
      }
    }
  }
}
