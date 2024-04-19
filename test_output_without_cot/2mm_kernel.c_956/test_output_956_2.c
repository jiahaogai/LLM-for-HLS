- #pragma ACCEL PIPELINE auto{off}: Do not automatically pipeline this loop.
- #pragma ACCEL TILE FACTOR=auto{1}: Keep this loop whole, without dividing it into smaller parts.
- #pragma ACCEL PARALLEL FACTOR=auto{1}: Execute loop iterations sequentially, not concurrently.
- #pragma ACCEL PARALLEL reduction = D FACTOR=auto{1}: Perform parallel reduction for the variable 'D'.
- #pragma ACCEL PIPELINE auto{off}: Do not automatically pipeline this loop.
- #pragma ACCEL TILE FACTOR=auto{1}: Keep this loop whole, without dividing it into smaller parts.
- #pragma ACCEL PARALLEL FACTOR=auto{1}: Execute loop iterations sequentially, not concurrently.
- #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}: This loop must be parallelized.
- #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}: This loop must be parallelized.

 
#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][80],double A[40][70],double B[70][50],double D[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp[i][j] = 0.0;
      for (k = 0; k < 70; ++k) {
        tmp[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=C[i] FACTOR=auto{__PARA__L2}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (k = 0; k < 50; k++) {
      
#pragma ACCEL PARALLEL reduction=C[i] FACTOR=auto{__PARA__L4}
      for (j = 0; j < 50; j++) {
        C[i][j] += alpha * D[k][j] * tmp[i][k];
      }
    }
  }
//#pragma endscop
}