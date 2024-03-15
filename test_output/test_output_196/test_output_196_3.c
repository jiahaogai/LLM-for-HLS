

"Automatically determine the parallelization factor for the inner loop, allowing up to 64 parallel instances"
```c
#pragma ACCEL PARALLEL FACTOR=auto{64}
```

#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
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
        z_diff[0] = hz[i][j] - hz[i][j + 1];
        z_diff[1] = hz[i][j + 1] - hz[i + 1][j + 1];
        z_diff[2] = hz[i + 1][j + 1] - hz[i + 1][j];
        x_y_diff = ex[i][j] - ex[i][j + 1];
        y_x_diff = ey[i][j] - ey[i + 1][j];
        hz[i][j] = hz[i][j] + 0.7 * (x_y_diff - 0.5 * (z_diff[0] + z_diff[1]));
        ey[i][j] = ey[i][j] + 0.7 * (z_diff[1] - z_diff[0]) + 0.079 * (y_x_diff - x_y_diff);
        ex[i][j] = ex[i][j] + 0.7 * (z_diff[0] - z_diff[2]) + 0.079 * (x_y_diff - y_x_diff);
      }
    }
  }
}
