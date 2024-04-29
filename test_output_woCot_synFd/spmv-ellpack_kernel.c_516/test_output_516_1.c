Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  spmv_1:
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: unknown type name ‘Automatically’
    2 |    Automatically determine the type of the parameter `nzval` to optimize the performance of system-level transformations.
      |    ^~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:28: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘the’
    2 |    Automatically determine the type of the parameter `nzval` to optimize the performance of system-level transformations.
      |                            ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:28: error: unknown type name ‘the’
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:54: error: stray ‘`’ in program
    2 |    Automatically determine the type of the parameter `nzval` to optimize the performance of system-level transformations.
      |                                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:60: error: stray ‘`’ in program
    2 |    Automatically determine the type of the parameter `nzval` to optimize the performance of system-level transformations.
      |                                                            ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘`’ in program
    4 | 6. `#pragma ACCEL PARAMS TYPE=auto{cols}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:5: error: stray ‘#’ in program
    4 | 6. `#pragma ACCEL PARAMS TYPE=auto{cols}`:
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:41: error: stray ‘`’ in program
    4 | 6. `#pragma ACCEL PARAMS TYPE=auto{cols}`:
      |                                         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:42: error: expected identifier or ‘(’ before ‘:’ token
    4 | 6. `#pragma ACCEL PARAMS TYPE=auto{cols}`:
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:54: error: stray ‘`’ in program
    5 |    Automatically determine the type of the parameter `cols` to optimize the performance of system-level transformations.
      |                                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:59: error: stray ‘`’ in program
    5 |    Automatically determine the type of the parameter `cols` to optimize the performance of system-level transformations.
      |                                                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:4: error: stray ‘