Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      idx = idx0;
      val = orig[idx0];
      idx1 = idx0 + 1;
      val += filter[0] * orig[idx1];
      idx2 = idx0 + 2;
      val += filter[1] * orig[idx2];
      idx3 = idx0 + 3;
      val += filter[2] * orig[idx3];
      idx4 = idx0 + 256;
      val += filter[3] * orig[idx4];
      idx5 = idx0 + 257;
      val += filter[4] * orig[idx5];
      idx6 = idx0 + 258;
      val += filter[5] * orig[idx6];
      idx7 = idx0 + 1;
      idx7 += 256;
      val += filter[6] * orig[idx7];
      idx8 = idx0 + 1;
      idx8 += 258;
      val += filter[7] * orig[idx8];
      idx = idx0;
      sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Body:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Function’; did you mean ‘union’?
    1 | ### Function Body:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Function Body:
      |                  ^

Please check the code and try again.