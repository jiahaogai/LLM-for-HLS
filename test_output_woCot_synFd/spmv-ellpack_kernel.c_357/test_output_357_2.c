Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum += val * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: unknown type name ‘Disable’
    2 |    Disable auto-pipelining to avoid excessive area usage.
      |    ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:17: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘off’
    2 |    Disable auto-pipelining to avoid excessive area usage.
      |                 ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 6. #pragma ACCEL PIPELINE auto{off}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:42: error: expected identifier or ‘(’ before ‘{’ token
    4 | 6. #pragma ACCEL PIPELINE auto{off}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:4: error: stray ‘#’ in program
    5 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:42: error: expected identifier or ‘(’ before ‘{’ token
    5 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:4: error: stray ‘#’ in program
    6 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:42: error: expected identifier or ‘(’ before ‘{’ token
    6 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACCEL PIPELINE auto{off}
      |  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACCEL PIPELINE auto{off}
      |  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACC