#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int jj;
  int kk;
  int i_row;
  int j_col;
  double temp_x;
  double mul;
=======
  int k_col;
  double mult;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
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
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      for (i = 0; i < 64; ++i) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
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
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (j = i; j < 64; j++) {
      C[i * 64 + j] *= beta;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      k_col = i * 64;
      
#pragma ACCEL PARALLEL reduction=mult FACTOR=auto{1}
      for (k = 0; k < 64; k++) {
        mult = alpha * A[k_col + k] * B[k * 64 + j];
        C[i * 64 + j] += mult;
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}