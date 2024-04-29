Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘-’ token
    1 | -
      | ^

Please check the code and try again.
 #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int k;
  int r_col;
  int c_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 2; c < 64 - 2; c++) {
      double temp = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        int r_idx = r - 2 + ((k / 3) * 128);
        int c_idx = c - 2 + ((k % 3) * 64);
        mult = filter[k] * orig[r_idx * 64 + c_idx];
        temp += mult;
      }
      sol[r * 64 + c] = temp;
    }
  }
}