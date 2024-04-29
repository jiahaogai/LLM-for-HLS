Code: #pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
=======
void kernel_spmv(double M[240][240],double vout[240],double vin[240],double zero,double one)
{
  int i;
  int j;
  double sum;
  double PI = 3.14159265358979323846;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 240; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 240; j++) {
      sum += M[i][j] * vin[j];
    }
    vout[i] = (sum + zero);
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_syrk(double A[240][240],double C[240][240],double zero,double one)
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
=======
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  syrk_1:
  for (i = 0; i < 240; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    syrk_2:
    for (j = 0; j < 240; j++) {
      C[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      syrk_3:
      for (k = 0; k < 240; k++) {
        mult = A[i][k] * A[k][j];
        C[i][j] += mult;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60],double zero,double one)
{
  int i;
  int j;
  int k;
  double mult;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
  syr2k_1:
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    syr2k_2:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
      for (j = 0; j < 60; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:13: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘for’
    3 | **Optimized for:**
      |             ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: stray ‘`’ in program
    4 | `quartus`
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:9: error: stray ‘`’ in program
    4 | `quartus`
      |         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: stray ‘`’ in program
    7 | `ISO C99`
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:9: error: stray ‘`’ in program
    7 | `ISO C99`
      |         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:12:1: error: stray ‘##’ in program
   12 | ### Function Parameters
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:12:3: error: stray ‘#’ in program
   12 | ### Function Parameters
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:1: error: stray ‘##’ in program
   22 | ### Functions
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:3: error: stray ‘#’ in program
   22 | ### Functions
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:1: error: stray ‘##’ in program
   27 | ### Function Files
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:3: error: stray ‘#’ in program
   27 |
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    syr2k_3:
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      syr2k_4:
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k] * B[k][j];
        C[i][j] += mult;
      }
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
