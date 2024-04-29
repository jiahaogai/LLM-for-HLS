Code: ### ACCEL kernel name: kernel_symm

### ACCEL PIPELINE auto{}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL FACTOR=auto{32}
  
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### ACCEL kernel name: kernel_symm
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### ACCEL kernel name: kernel_symm
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘ACCEL’
    1 | ### ACCEL kernel name: kernel_symm
      |     ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘name’
    1 | ### ACCEL kernel name: kernel_symm
      |                  ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: error: stray ‘##’ in program
    3 | ### ACCEL PIPELINE auto{}
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘#’ in program
    3 | ### ACCEL PIPELINE auto{}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:1: error: stray ‘##’ in program
    5 | ### ACCEL TILE FACTOR=auto{1}
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: error: stray ‘#’ in program
    5 | ### ACCEL TILE FACTOR=auto{1}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:5: error: unknown type name ‘ACCEL’
    5 | ### ACCEL TILE FACTOR=auto{1}
      |     ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:16: error: expected ‘=’, ‘,’, ‘;