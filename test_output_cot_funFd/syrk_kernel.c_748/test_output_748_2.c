#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNI
// => Form C := alpha*A*A**T + beta*C,
  int ni = 80;
  int nj = 80;
  int nk = 60;
  double tmp;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{6}
      for (k = 0; k < 60; k++) {
        mul = alpha * A[i][k];
        tmp += mul * A[j][k];
      }
      C[i][j] += tmp * beta;
    }
  }
}