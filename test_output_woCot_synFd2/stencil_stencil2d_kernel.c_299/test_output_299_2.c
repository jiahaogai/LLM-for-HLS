Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
      inner:
      for (k = -1; k <= 1; k++) {
        int _in;
        int _out;
        _in = pad + ((i * 8) + j) * 8 + k;
        _out = _in;
        if (((_in + 8192) > 8191) || ((_in + 8) < 0)) {
          _out = pad - 1;
        }
        t += filter[((k + 1) << 3) + 5] * orig[_out];
      }
      sol[_in] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:43:11: error: ‘_in’ undeclared (first use in this function)
   43 |       sol[_in] = t;
      |           ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:43:11: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
      inner:
      for (k = -1; k <= 1; k++) {
        int _in;
        int _out;
        _in = pad + ((i * 8) + j) * 8 + k;
        _out = _in;
        if (((_in + 8192) > 8191) || ((_in + 8) < 0)) {
          _out = pad - 1;
        }
        t += filter[((k + 1) << 3) + 5] * orig[_out];
      }
      sol[_in] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl