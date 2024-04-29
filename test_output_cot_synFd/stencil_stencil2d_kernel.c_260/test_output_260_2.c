Code: #pragma ACCEL kernel

void stencil(out int sol[8192],in int orig[8192],in int filter[9])
{
  int i;
  int j;
  int k;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    int sum = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 9; j++) {
      int tmp_flattened = 0;
      
#pragma ACCEL PARALLEL reduction=tmp_flattened FACTOR=auto{8}
      inner:
      for (k = 0; k < 8; k++) {
        tmp_flattened += orig[i * 8 + k] * filter[j * 8 + k];
      }
      flit = tmp_flattened;
      sum += flit;
    }
    sol[i] = sum;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:14: error: unknown type name ‘out’
    3 | void stencil(out int sol[8192],in int orig[8192],in int filter[9])
      |              ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:32: error: unknown type name ‘in’; did you mean ‘int’?
    3 | void stencil(out int sol[8192],in int orig[8192],in int filter[9])
      |                                ^~
      |                                int
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:50: error: unknown type name ‘in’; did you mean ‘int’?
    3 | void stencil(out int sol[8192],in int orig[8192],in int filter[9])
      |                                                  ^~
      |                                                  int

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(out int sol[8192],in int orig[8192],in int filter[9])
{
  int i;
  int j;
  int k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        sum += orig[i * 256 + j] * filter[k];
      }
      sol[i * 256 + j] = sum;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:14: error: unknown type name ‘out’
    3 | void stencil(out int sol[8192],in int orig[8192],in int filter[9])