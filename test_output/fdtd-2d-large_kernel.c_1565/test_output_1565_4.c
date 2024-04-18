#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
        double e0;
        double e1;
        double e2;
        double n0;
        double n1;
        double n2;
        double s0;
        double s1;
        double s2;
        double w0;
        double w1;
        double w2;
        double e;
        double n;
        double s;
        double w;
        double tmp;
        e0 = ex[i][j];
        e1 = ex[i][j + 1];
        e2 = ex[i][j + 2];
        n0 = ey[i][j];
        n1 = ey[i][j + 1];
        n2 = ey[i][j + 2];
        s0 = ey[i + 1][j];
        s1 = ey[i + 1][j + 1];
        s2 = ey[i + 1][j + 2];
        w0 = ey[i + 2][j];
        w1 = ey[i + 2][j + 1];
        w2 = ey[i + 2][j + 2];
        e = ((e2 * s  +  e1 * s2  +  e0 * s1 ) - (w0 * n  +  w1 * n0  +  w2 * n1 )) / ((s  -  n ));
        n = ((n2 * e  +  n1 * e2  +  n0 * e1 ) - (w0 * s  +  w1 * s0  +  w2 * s1 )) / ((s  -  n ));
        s = ((s2 * e  +  s1 * e2  +  s0 * e1 ) - (n0 * w  +  n1 * w0  +  n2 * w1 )) / ((s  -  n ));
        w = ((w2 * e  +  w1 * e2  +  w0 * e1 ) - (s0 * n  +  s1 * n0  +  s2 * n1 )) / ((s  -  n ));
        tmp = e;
        ex[i][j] = tmp;
        tmp = n;
        ey[i][j] = tmp;
        ey[i][j + 1] = s;
        ex[i][j + 1] = w;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240; j++) {
        double tmp_0;
        double tmp_1;
        tmp_0 = ex[i][j] + _fict_[i];
        tmp_1 = ey[i][j] + tmp_0;
        hz[i][j] = tmp_1;
      }
    }
  }
}