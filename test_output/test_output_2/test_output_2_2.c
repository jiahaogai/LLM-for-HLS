
 #pragma ACCEL kernel

void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
    }
  }
  
#pragma ACCEL PIPELINE auto{_auto_pipeline_0}
  
#pragma ACCEL TILE FACTOR=auto{_auto_tile_0}
  
#pragma ACCEL PARALLEL FACTOR=auto{_auto_parallel_0}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{_auto_pipeline_1}
    
#pragma ACCEL TILE FACTOR=auto{_auto_tile_1}
    
#pragma ACCEL PARALLEL FACTOR=auto{_auto_parallel_1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L2}
      for (j = 0; j < 220; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
