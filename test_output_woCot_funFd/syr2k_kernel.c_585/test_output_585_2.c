**Optimized for**: 
avx

**Input Arguments**:

| TYPE        | NAME    | RANGE | SCALE | DIST | COMMENT |
| ----------- | ------- | ----- | ----- | ----- | ------- |
| double      | alpha   | 0.0   | 1.0   |       |         |
| double      | beta    | 0.0   | 1.0   |       |         |
| double[80]  | C[80][80] | 0   | 1.0   |     |         |
| double[80]  | A[80][60] | 0   | 1.0   |     |         |
| double[80]  | B[80][60] | 0   | 1.0   |     |         |

**Output Arguments**:

| TYPE        | NAME    | RANGE | SCALE | DIST | COMMENT |
| ----------- | ------- | ----- | ----- | ----- | ------- |
| double[80]  | C[80][80] | 0   | 1.0   |     |         |

**Invariant Arguments**:

| NAME    | TYPE        | RANGE | SCALE | DIST | COMMENT |
| ------- | ----------- | ----- | ----- | ----- | ------- |
| A       | double[80]  | 0   | 1.0   |     |         |
| B       | double[80]  | 0   | 1.0   |     |         |
| C       | double[80]  | 0   | 1.0   |     |         |
| alpha   | double      | 0.0   | 1.0   |       |         |
| beta    | double      | 0.0   | 1.0   |       |         |

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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{5}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}