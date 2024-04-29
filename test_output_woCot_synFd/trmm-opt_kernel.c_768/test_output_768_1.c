Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_trmm() {
  int i;
  int j;
  int k;
  int k_col;
  double sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        k_col = i * 60 + k;
        sum += A[k][j] * B[k_col][i];
      }
      A[j][i] = sum;
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_trmm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:16: error: ‘A’ undeclared (first use in this function)
   30 |         sum += A[k][j] * B[k_col][i];
      |                ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:16: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:26: error: ‘B’ undeclared (first use in this function)
   30 |         sum += A[k][j] * B[k_col][i];
      |                          ^

Please check the code and try again.
Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_trmm() {
  int i;
  int j;
  int k;
  int k_col;
  double sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        k_col = i * 60 + k;
        sum += A[k][j] * B[k_col][i];
      }
      A[j][i] = sum;
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_trmm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:16: error: ‘A’ undeclared (first use in this function)
   30 |         sum += A[k][j] * B[k_col][i];
      |