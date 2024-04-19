- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the following loop with tilesize=1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Automatically parallelize the following loop, with 1 tasks.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`: Automatically parallelize the following loop, with __PARA__L2 tasks.
- `#pragma ACCEL PIPELINE auto{__PIPE__L2}`: Automatically pipeline the following loop with pipelinedepth=__PIPE__L2.
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}`: Tile the following loop with tilesize=__TILE__L2.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}`: Automatically parallelize the following loop, with __PARA__L3 tasks.
- `#pragma ACCEL PIPELINE auto{__PIPE__L3}`: Automatically pipeline the following loop with pipelinedepth=__PIPE__L3.
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L3}`: Tile the following loop with tilesize=__TILE__L3.
- `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}`: Automatically parallelize the following loop, with __PARA__L4 tasks.
- `#pragma ACCEL PIPELINE auto{__PIPE__L4}`: Automatically pipeline the following loop with pipelinedepth=__PIPE__L4.
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L4}`: Tile the following loop with tilesize=__TILE__L4.

### Original Kernel
  #pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (k = 0; k < 70; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
      
#pragma ACCEL PARALLEL reduction=D FACTOR=auto{1}
      for (k = 0; k < 50; ++k) {
        D[i][j] += tmp[i][k] * C[k][j];
      }
    }
  }
//#pragma endscop
}