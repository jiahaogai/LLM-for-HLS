

5. "Transform this for loop automatically into a parallelized form by unrolling it automatically" - Use `#pragma ACCEL PARALLEL FACTOR=auto{1}` to specify that the parallelization factor should be automatically decided by ACCEL. The number 1 is used to unroll the loop by a factor of 1.

6. "Transform this for loop automatically into a parallelized form by unrolling it automatically and breaking it down by tiles of 4" - Use `#pragma ACCEL PIPELINE auto{off}`
	
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
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
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
        int i_col = -1;
        int j_col = -1;
        double ey_x = (ey[i][j + 1] - ey[i][j]) / (ex[i][j + 1] - ex[i][j]);
        double ex_y = (ex[i + 1][j] - ex[i][j]) / (ey[i + 1][j] - ey[i][j]);
        double _tmp_ = ex[i][j] + (1.0 - 2.0 * rdt) * hz[i][j] + rdt * (ex_y + ey_x);
        hz[i][j] = hz[i][j] + (1.0 - 2.0 * rdt) * _tmp_ + rdt * (hz[i + 1][j] - hz[i][j + 1]);
        ey[i][j] = ey[i][j] + rdt * (_tmp_ - hz[i][j]);
        ex[i][j] = ex[i][j] + rdt * (hz[i][j] - _tmp_);
      }
    }
  }
}
