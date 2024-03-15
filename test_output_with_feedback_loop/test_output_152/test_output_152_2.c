#pragma ACCEL PARAMETER TRI_A = 120
#pragma ACCEL PARAMETER TRI_B = 120
#pragma ACCEL PARAMETER TRI_C = 140

void kernel_gemm(double alpha,double beta,double C[140][140],double A[140][120],double B[140][120])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//SIDE = 'L'
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is MxK
//B is KxN
//C is MxN
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 140; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 140; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 120; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L3}
      for (j = 0; j < 140; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}