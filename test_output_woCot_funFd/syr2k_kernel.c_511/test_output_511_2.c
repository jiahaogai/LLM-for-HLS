#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[400][400],double A[400][500],double B[500][400])
=======
void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NROWA x NCOLA
//B is NCOLA x NROWB
//C is NROWA x NROWA
=======
  int jj;
  int kk;
  int i_row;
  int j_col;
  double temp_x;
  double mul;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 400; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 500; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 400; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
=======
  loopjj:
/* Standardize from: for(jj = 0;jj < 64;jj += 8) {...} */
  for (jj = 0; jj <= 7; jj++) {
    int _in_jj = 0 + 8L * jj;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopkk:
/* Standardize from: for(kk = 0;kk < 64;kk += 8) {...} */
    for (kk = 0; kk <= 7; kk++) {
      int _in_kk = 0 + 8L * kk;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      for (i = 0; i < 64; ++i) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{4}
        loopj:
        for (j = 0; j < 8; ++j) {
          i_row = i * 64;
          j_col = (j + _in_jj) * 64;
          temp_x = alpha * A[i_row + j + _in_jj];
          loopk:
          for (k = 0; k < 8; ++k) {
            mul = temp_x * B[j_col + k + _in_kk];
            C[i_row + k + _in_kk] += mul;
          }
        }
      }
    }
    kk = 56 + 8L;
  }
  jj = 56 + 8L;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}