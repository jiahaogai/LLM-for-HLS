Code: ### #pragma ACCEL kernel

### 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{10}

#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{80}
#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{4}
  
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for(int i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for(int j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for(int k = 0; k < 60; k++) {
        double prod = A[i][k] * B[k][j];
        sum += prod;
      }
      temp2[i][j] = sum;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for(int j = 0; j < 80; j++) {
      C[i][j] += temp2[i][j] * alpha;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:6: error: unknown type name ‘pragma’; did you mean ‘_Pragma’?
    1 | ### #pragma ACCEL kernel
      |      ^~~~~~
      |      _Pragma
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:19: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘kernel’
    1 | ### #pragma ACCEL kernel
      |                   ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: error: stray ‘##’ in program
    3 | ### 
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘#’ in program
    3 | ### 
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:20: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
   20 |   for(int i = 0; i < 60; i++) {
      |                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:27: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__