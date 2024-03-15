
5. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
    for (j = 16; j < 64; j++) {
      b[j] = b[j] + b[j - 16];
    }

6. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 64; i++) {
      a[i] = a[i] + a[i - 1];
      tmp = a[i] * b[i];
      c[i] = tmp + c[i - 1];
    }

7. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 63; i >= 16; i--) {
      b[i] = b[i] + b[i - 1];
    }

8. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 15; i < 64; i++) {
      tmp2 = c[i];
      SIMD_LFCT2 tmp3 = a[i] * b[i];
      SIMD_LFCT2 tmp4 = tmp3 * (SIMD_LF)1.5;
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = i + 1; j < 64; j++) {
        tmp2 = tmp2 + a[j] * b[j];
      }
      c[i] = tmp2 + tmp4;
    }
// Matrix multiplication
  
#pragma ACCEL kernel

void kernel_gemm(int ni,int nj,int nk,double A[60][80],double B[60][90],double C[80][90])
{
  int i;
  int j;
  int k;
//#pragma scop
/* Standardize from: for(i = 0;i < 60;++i) {...} */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
/* Standardize from: for(j = 0;j < 80;++j) {...} */
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      A[i][j]:A[0][0];
      B[i][j]:B[0][0];
      C[i][j]:C[0][0] = ((double )0);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 90; k++) {
/* Standardize from: for(j = 0;j < 80;++j) {...} */
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][k]:C[0][0];
        A[i][k] * B[k][j]
        ;
      }
    }
  }
//#pragma endscop
}
