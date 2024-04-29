#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
=======
void kernel_syr2k(double alpha,double beta,double C[250][250],double A[250][250],double B[250][250])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int j_col;
  int k_row;
  double mult;
=======
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  for (i = 0; i < 64; i++) {
=======
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
    for (j = 0; j < 250; j++) {
      C[i][j] *= beta;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = i; j < 64; j++) {
      j_col = j * 64;
      C[j_col + i] *= beta;
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (k = 0; k < 64; k++) {
        k_row = k * 64;
        mult = alpha * A[k_row + i] * B[j_col + k];
        C[j_col + i] += mult;
      }
    }
  }
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 250; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 250; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}