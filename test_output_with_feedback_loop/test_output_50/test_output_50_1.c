- Do not distribute the computation of this loop over the threads: `#pragma ACCEL PARALLEL FACTOR=auto{1}`
- Do not vectorize the computation of this loop: `#pragma ACCEL PARALLEL FACTOR=auto{16} VECTOR=off`
- Do not unroll the computation of this loop: `#pragma ACCEL PARALLEL FACTOR=auto{1} UNROLL=off`
- Do not parallelize the computation of this loop on the outer loop: `#pragma ACCEL PIPELINE auto{off} {_pipeline_off}`
- Do not parallelize the computation of this loop on the inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L2} {__PIPE__L2}`
- Do not parallelize the computation of this loop on the inner-inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L3} {__PIPE__L3}`
- Do not parallelize the computation of this loop on the outer-outer loop: `#pragma ACCEL PIPELINE auto{off} {_pipeline_off}`
- Do not parallelize the computation of this loop on the outer-middle loop: `#pragma ACCEL PIPELINE auto{__PIPE__L1} {__PIPE__L1}`
- Do not parallelize the computation of this loop on the middle-middle loop: `#pragma ACCEL PIPELINE auto{__PIPE__L4} {__PIPE__L4}`
- Do not parallelize the computation of this loop on the middle-inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L5} {__PIPE__L5}`
- Do not parallelize the computation of this loop on the outer-inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L6} {__PIPE__L6}`
- Do not parallelize the computation of this loop on the outer-outer loop: `#pragma ACCEL PIPELINE auto{off} {_pipeline_off}`
- Do not parallelize the computation of this loop on the outer-middle loop: `#pragma ACCEL PIPELINE auto{__PIPE__L1} {__PIPE__L1}`
- Do not parallelize the computation of this loop on the middle-middle loop: `#pragma ACCEL PIPELINE auto{__PIPE__L4} {__PIPE__L4}`
- Do not parallelize the computation of this loop on the middle-inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L5} {__PIPE__L5}`
- Do not parallelize the computation of this loop on the outer-inner loop: `#pragma ACCEL PIPELINE auto{__PIPE__L6} {__PIPE__L6}`
  
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
        int _row = i * 240 + j;
        hz[i][j] = hz[i][j] - 0.7 * (ex[i][j + 1] - ex[i][j] + ey[i + 1][j] - ey[i][j]);
      }
    }
  }
}