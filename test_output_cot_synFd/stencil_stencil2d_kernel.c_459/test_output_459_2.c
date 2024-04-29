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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t = t + filter[((k + pad) * 3) + (jj + pad)] * orig[((i + k) * 64) + ((j + jj) * 1)] * orig[((i * 64) + (j * 1))];
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:14: error: ‘jj’ undeclared (first use in this function); did you mean ‘j’?
   27 |         for (jj = -1 * pad; jj <= 1 * pad; jj++) {
      |              ^~
      |              j
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:14: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.