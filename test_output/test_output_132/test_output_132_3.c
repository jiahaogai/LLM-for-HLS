  
#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{64}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        double  delta = 1.0 / ((double )(1 << 12));
        double  p1 = ex[i][j] - ex[i][j + 1];
        double  p2 = ey[i][j] - ey[i + 1][j];
        double  p3 = hz[i][j] - hz[i + 1][j];
        double  p4 = ex[i][j + 1] + ex[i][j] - ey[i + 1][j] - ey[i][j];
        double  p5 = ey[i][j + 1] + ey[i][j] - hz[i][j] - hz[i][j + 1];
        double  num1 = p4 * p4;
        double  num2 = 4.0 * p3 * p5;
        double  den = num1 + num2;
        hz[i][j] = hz[i][j] + delta * (p1 * num2 - p2 * num1 + p3 * (p4 + p5));
        ey[i][j] = ey[i][j] + delta * (p1 * num2 + p2 * num1 + p3 * (p4 - p5));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240 - 1; j++) {
        double  delta = 1.0 / ((double )(1 << 12));
        double  p1 = ex[i][j] - ex[i][j + 1];
        double  p2 = ey[i][j] - ey[i + 1][j];
        double  p3 = hz[i][j] - hz[i + 1][j];
        double  p4 = ex[i][j + 1] + ex[i][j] - ey[i + 1][j] - ey[i][j];
        double  p5 = ey[i + 1][j + 1] + ey[i][j + 1] - hz[i + 1][j + 1] - hz[i][j + 1];
        double  num1 = p4 * p4;
        double  num2 = 4.0 * p3 * p5;
        double  den = num1 + num2;
        ex[i][j] = ex[i][j] + delta * (p1 * num2 - p2 * num1 + p3 * (p4 + p5));
      }
    }
  }
}
