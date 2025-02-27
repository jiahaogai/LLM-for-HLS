Code: ### Parameters:

* `alpha` - double  
* `beta` - double  
* `C` - double[60][80]  
* `A` - double[60][60]  
* `B` - double[60][80]
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Parameters:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Parameters:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Parameters:
      |               ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | * `alpha` - double
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:9: error: stray ‘`’ in program
    3 | * `alpha` - double
      |         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘`’ in program
    4 | * `beta` - double
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:8: error: stray ‘`’ in program
    4 | * `beta` - double
      |        ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: error: stray ‘`’ in program
    5 | * `C` - double[60][80]
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:5: error: stray ‘`’ in program
    5 | * `C` - double[60][80]
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:3: error: stray ‘`’ in program
    6 | * `A` - double[60][60]
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:5: error: stray ‘`’ in program
    6 | * `A` - double[60][60]
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:3: error: stray ‘`’ in program
    7 | * `B` - double[60][80]
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:5: error: stray ‘`’ in program
    7 | * `B` - double[60][80]
      |     ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;