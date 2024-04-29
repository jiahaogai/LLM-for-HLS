Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 80; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{1} 
  for (j = 0; j < 80; j++) {
    if (j <= i) {
      C[i][j] *= beta;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (k = 0; k < 60; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      if (j <= i) {
        C[i][j] += A[j][k] * alpha * B[i][k] + B[j][k] * alpha * A[i][k];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: expected identifier or ‘(’ before ‘for’
    6 | for (i = 0; i < 80; i++) {
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
    6 | for (i = 0; i < 80; i++) {
      |               ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:22: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘++’ token
    6 | for (i = 0; i < 80; i++) {
      |                      ^~

Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 80; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{1} 
  for (j = 0; j < 80; j++) {
    if (j <= i) {
      C[i][j] *= beta;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (k = 0; k < 60; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      if (j <= i) {
        C[i][j] += A[j][k] * alpha * B[i][k] + B[j][k] * alpha * A[i][k];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: expected identifier or ‘(’ before ‘for’
    6 | for (i = 0; i < 80; i++) {
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
    6 | for (i = 0; i < 80; i++) {
      |               ^
/root/aut