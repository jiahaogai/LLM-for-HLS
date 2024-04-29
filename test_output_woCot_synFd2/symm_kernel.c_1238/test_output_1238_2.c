Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
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
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{60}
        for (jj = 0; jj < 60; jj++) {
          temp2 += A[i][jj] * B[jj][j];
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:13: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘for’
    4 | **Optimized for:**
      |             ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:36: error: invalid suffix "md" on floating constant
    5 |  - [x86-64](/environment/archs/x86-64.md)
      |                                    ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:9:19: error: invalid suffix "Kb" on floating constant
    9 | **Input size:** ~ 21.5Kb
      |                   ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:39: error: invalid suffix "Kb" on floating constant
   16 | **Generated (compiled) file size:** ~ 39.6Kb
      |                                       ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:19:49: error: invalid suffix "csv" on floating constant
   19 |     - [x86-64](/kernels/level_3/kernel_symm.x86-64.csv) 4.60 GFLOPS
      |                                                 ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:1: error: stray ‘##’ in program
   26 | ### Flat
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:3: error: stray ‘#’ in program
   26 | ### Flat
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:28:45: error: invalid suffix "