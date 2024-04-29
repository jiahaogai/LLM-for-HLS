Code: ### Arrays:
C: 80 x 80  
A: 80 x 60  
B: 80 x 60  

### Parameters:
alpha: 1.3  
beta: 1.5  

### Functions:
  
#pragma ACCEL kernel  
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{1}  
  
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
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{1}  
  for (i = 0; i < 80; i++) {  
    
#pragma ACCEL PARALLEL FACTOR=auto{1}  
    for (j = 0; j < 80; j++) {  
      C[i][j] *= beta;  
    }  
    
#pragma ACCEL PIPELINE auto{}  
    
#pragma ACCEL TILE FACTOR=auto{1}  
    
#pragma ACCEL PARALLEL FACTOR=auto{2}  
    for (k = 0; k < 60; k++) {  
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}  
      for (j = 0; j < 80; j++) {  
        C[i][j] += alpha * A[i][k] * B[k][j];  
      }  
    }  
  }  
}