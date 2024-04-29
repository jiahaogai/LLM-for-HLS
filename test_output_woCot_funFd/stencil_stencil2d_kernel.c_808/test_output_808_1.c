Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int flatten_idx;
  int range_l;
  int range_r;
  int idx_in;
  int idx_out;
  int t;
  range_l = 0 - 1;
  range_r = 8191 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0 + 0; j < 64 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 0 + 0; i < 128 + 0; i++) {
      idx_out = i + j * 128;
      idx_in = i - 1 + ((j - 1) * 128);
      flatten_idx = idx_in + range_l;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = 0; k < 9; k++) {
        idx = flatten_idx + space[k];
        if (idx < range_l) {
          idx = range_l;
        }
        else if (idx > range_r) {
          idx = range_r;
        }
        t = orig[idx];
        sol[idx_out] = t * filter[k];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | #pragma ACCEL kernel
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:32: error: expected identifier or ‘(’ before ‘{’ token
    2 | #pragma ACCEL kernel
      |                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: error: expected identifier or ‘(’ before ‘int’
    3 |   int i;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:1: warning: unused variable i
    3 |   int i;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: expected identifier or ‘(’ before ‘int’
    4 |   int j;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: warning: unused variable j
    4 |   int j;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:1: error: expected identifier or ‘(’ before ‘int’
    5 |   int k;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:1: warning: unused variable k
    5 |   int k;
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1