Code: #pragma ACCEL kernel

### Parameters

 | Name | Type | Description |
 | ---- | ---- | ----------- |
 | alpha | double | scalar multiplier |
 | beta | double | scalar multiplier |
 | C | double[80][80] | output matrix |
 | A | double[80][60] | input matrix |

### Local Variables

   | Name | Type | Description |
   | ---- | ---- | ----------- |
   | i | int | loop counter for matrix A |
   | j | int | loop counter for matrix C |
   | k | int | loop counter for matrix A |
   | tmp | double | accumulator |

### Detailed Description

   ALPHA is multiplied with the original matrix A, and the result is added to the original matrix C, row-by-row.
    
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: error: expected identifier or ‘(’ before ‘-’ token
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static: Chunk sizes at each level are fixed.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static: Chunk sizes at each level are fixed.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static: Chunk sizes at each level are fixed.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:50: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘{’ token
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static: Chunk sizes at each level are fixed.
      |                                                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:59: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static: Chunk sizes at each level are fixed.
      |                                                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:61: error: expected identifier or ‘(’ before ‘:’ token
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1} SCHEDULE{static}` : Static