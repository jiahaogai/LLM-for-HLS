**Optimized for:**
`autopilot`

**AutoPilot language:**
`c`

**Returns:**
None

**Variables:**
 - `alpha`
T: double
 - `beta`
T: double
 - `C`
T: double[80][80]
 - `A`
T: double[80][60]
 - `B`
T: double[80][60]

**Constraints:**

**Preprocessor Defints:**
 - `TILEFACTOR=4`
 - `PIPEFACTOR=1`
 - `A_COLS=60`
 - `A_ROWS=80`
 - `B_COLS=60`
 - `B_ROWS=80`
 - `C_COLS=80`
 - `C_ROWS=80`
 - `PARA_A=16`
 - `PARA_B=16`
 - `PARA_C=8`

**Code:**
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}