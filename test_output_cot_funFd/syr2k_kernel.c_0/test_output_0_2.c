The `#pragma ACCEL PARAMS` directive introduces parameters `N`, `M`, `alpha`, `beta`, `A[N,M]`, `B[N,M]`, `C[N,N]`, and `C_out[N,N]` for the function.

#pragma ACCEL kernel

void kernel_syr2k(int n,int m,double alpha,double beta,double C[40][40],double A[40][30],double B[40][30],double C_out[40][40])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NIxNK
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 40; j++) {
      C_out[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 30; ++k) {
        C_out[i][j] += alpha * A[i][k] * B[k][j];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 30; ++k) {
        C_out[i][j] += alpha * B[i][k] * A[k][j];
      }
      C_out[i][j] += beta * C[i][j];
    }
  }
}