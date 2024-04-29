Code: #pragma ACCEL kernel

void kernel_symm(int ni,int nj,double alpha,double beta,double C[60][70],double A[60][80],double B[80][70])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIx80
//B is 80xNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 70; j++) {
        double temp2 = 0.0;
        double temp1 = 0.0;
        for (l = 0; l < 80; l++) {
          temp1 += A[i][l] * B[l][j];
        }
        temp2 = temp1 + C[i][j];
        C[i][j] = temp2;
      }
    }
  }
}