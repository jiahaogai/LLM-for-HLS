Code: #pragma ACCEL kernel

void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_t;
  int cols_t;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      nzval_t = nzval[j];
      cols_t = cols[j];
      sum += nzval_t * vec[cols_t];
    }
    out[i] = sum;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: expected identifier or ‘(’ before ‘-’ token
    2 |    - Translate: Create a parameter called `nzval` of type `double[]`.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:43: error: stray ‘`’ in program
    2 |    - Translate: Create a parameter called `nzval` of type `double[]`.
      |                                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:49: error: stray ‘`’ in program
    2 |    - Translate: Create a parameter called `nzval` of type `double[]`.
      |                                                 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:59: error: stray ‘`’ in program
    2 |    - Translate: Create a parameter called `nzval` of type `double[]`.
      |                                                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:68: error: stray ‘`’ in program
    2 |    - Translate: Create a parameter called `nzval` of type `double[]`.
      |                                                                    ^
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
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:43: error: stray ‘`’ in program
    5 |    - Translate: Create a parameter called `cols` of type `int[]`.
      |                                           ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:48: error: stray ‘`’ in program
    5 |    - Translate: Create a parameter called `cols` of type `int[]`.