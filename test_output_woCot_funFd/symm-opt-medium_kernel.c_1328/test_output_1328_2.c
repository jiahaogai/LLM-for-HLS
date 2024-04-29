Code: ###
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 240; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ###
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ###
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘PRAGMA’
    1 | ###
      |     ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:13: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘kernel’
    1 | ###
      |             ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:13: error: unknown type name ‘kernel’
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:1: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘The’
    5 | The scalar alpha.
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:1: error: unknown type name ‘The’
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘double’
    6 |   double beta
      | ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: unknown type name ‘double’
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘C’
    7 |   double C[200][240]
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: unknown type name ‘C’
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:1: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘A’
    8 |   double A[200][200]