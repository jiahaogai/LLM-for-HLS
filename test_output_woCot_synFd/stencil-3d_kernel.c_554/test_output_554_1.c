Code: #pragma ACCEL kernel

void kernel_3mm(long C0,long C1,long C2,long A[320][320],long B[320][320],long F[320][320])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 320; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 320; j++) {
      F[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{2}
      loop_k:
      for (k = 0; k < 320; k++) {
        F[i][j] += A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: expected identifier or ‘(’ before ‘-’ token
    2 |    - Explanation: Prevent the automatic pipelining of the outer loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘`’ in program
    3 | 8. `#pragma ACCEL PIPELINE auto{off}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:5: error: stray ‘#’ in program
    3 | 8. `#pragma ACCEL PIPELINE auto{off}`:
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:37: error: stray ‘`’ in program
    3 | 8. `#pragma ACCEL PIPELINE auto{off}`:
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:38: error: expected identifier or ‘(’ before ‘:’ token
    3 | 8. `#pragma ACCEL PIPELINE auto{off}`:
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘`’ in program
    4 | 9. `#pragma ACCEL TILE FACTOR=auto{1}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:5: error: stray ‘#’ in program
    4 | 9. `#pragma ACCEL TILE FACTOR=auto{1}`:
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:38: error: stray ‘`’ in program
    4 | 9. `#pragma ACCEL TILE FACTOR=auto{1}`:
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:39: error: expected identifier or ‘(’ before ‘:’ token
    4 | 9. `#pragma ACCEL TILE FACTOR=auto{1}`:
      |                                       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:4: error: stray ‘`’ in program
    6 | 10. `#pragma ACCEL PIPELINE auto{off}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:5