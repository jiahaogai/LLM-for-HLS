#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[60][80],double ey[60][80],double hz[60][80],double _fict_[40])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2_0}
    for (j = 0; j < 80; j++) {
      ey[0][j] = _fict_[j];
    }
    
#pragma ACCEL PIPELINE auto{off_1}
    
#pragma ACCEL TILE FACTOR=auto{1_1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2_1}
    for (i = 1; i < 60; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2_1_0}
      for (j = 0; j < 80; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off_2}
    
#pragma ACCEL TILE FACTOR=auto{1_2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2_2}
    for (i = 0; i < 60; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2_2_0}
      for (j = 1; j < 80; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off_3}
    
#pragma ACCEL TILE FACTOR=auto{1_3}
    
#pragma ACCEL PARALLEL FACTOR=auto{2_3}
    for (i = 0; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2_3_0}
      for (j = 0; j < 79; j++) {
        hz[i][j] = hz[i][j] - 0.7 * (ex[i][j + 1] - ex[i][j] + ey[i + 1][j] - ey[i][j]);
      }
    }
  }
//#pragma endscop
}