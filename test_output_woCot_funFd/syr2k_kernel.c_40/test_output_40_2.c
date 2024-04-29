#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
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
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      double ajk = 0.0;
      
#pragma ACCEL PARALLEL reduction=ajk FACTOR=auto{8}
      for (i = 0; i < 80; i++) {
        ajk += A[i][k] * B[i][j];
      }
      ajk *= alpha;
      C[k][j] += ajk;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      double bjk = 0.0;
      
#pragma ACCEL PARALLEL reduction=bjk FACTOR=auto{8}
      for (i = 0; i < 80; i++) {
        bjk += B[i][k] * A[i][j];
      }
      bjk *= alpha;
      C[k][j] += beta * C[k][j] + bjk;
    }
  }
  
#pragma endscop
}