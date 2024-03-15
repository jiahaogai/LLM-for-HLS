
- Use #pragma ACCEL PARALLEL FACTOR=__PARA__L4 __PARA__L5 to parallelize the loop with the specified parallelization factors.
- Use #pragma ACCEL PIPELINE auto{__PIPE__L4} to pipeline the loop with the specified pipeline identifier.
- Use #pragma ACCEL TILE FACTOR=__TILE__L4 to break the loop into smaller chunks and specify a tile identifier.
- Use #pragma ACCEL PARALLEL FACTOR=__PARA__L6 to run the iterations of the loop in parallel with the specified parallelization factor.
 
#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240 - 1; j++) {
        int i_0 = i;
        int j_0 = j;
        hz[i_0][j_0] = hz[i_0][j_0] - 0.7 * (ex[i_0][j_0 + 1] - ex[i_0][j_0] + ey[i_0 + 1][j_0] - ey[i_0][j_0]);
      }
    }
  }
}
