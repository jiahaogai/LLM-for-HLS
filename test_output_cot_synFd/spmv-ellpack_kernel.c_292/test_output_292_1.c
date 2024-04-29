Code: #pragma ACCEL kernel

void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: expected identifier or ‘(’ before ‘-’ token
    2 |    - Translate: Provide a hint to use a tile factor of 2 for the nzval and cols arrays.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘`’ in program
    4 | 6. `#pragma ACCEL PARAMS FACTOR=auto{16}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:5: error: stray ‘#’ in program
    4 | 6. `#pragma ACCEL PARAMS FACTOR=auto{16}`:
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:41: error: stray ‘`’ in program
    4 | 6. `#pragma ACCEL PARAMS FACTOR=auto{16}`:
      |                                         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:42: error: expected identifier or ‘(’ before ‘:’ token
    4 | 6. `#pragma ACCEL PARAMS FACTOR=auto{16}`:
      |                                          ^

Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

void kernel_spmv(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: expected identifier or ‘(’ before ‘-’ token
    2 |    - Translate: Turn off pipelining for this loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘`’ in program
    4 | 6. `#pragma ACCEL PIPELINE auto{off}`:
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:5: error: stray ‘#’ in program
    4 | 6. `#pragma ACCEL PIPELINE auto{off}`:
      |     ^
/root/autodl-tmp/LLM/