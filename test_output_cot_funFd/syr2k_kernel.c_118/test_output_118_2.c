#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][80],double B[80][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*C + beta*A*B**T
  for (i = 0; i < 80; i++) {
     for (j = 0; j < 80; j++) {
       C[i][j] *= beta;
     }
     for (k = 0; k < 80; k++) {
       for (j = 0; j < 80; j++) {
         C[i][j] += alpha * A[i][k] * B[k][j];
       }
     }
   }
}