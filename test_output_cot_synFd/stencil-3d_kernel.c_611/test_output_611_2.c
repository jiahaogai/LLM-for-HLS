Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[25][25][25],long sol[25][25][25])
{
  long i;
  long j;
  long k;
  long ko;
  long kd;
  long jd;
  long i_col;
  long j_col;
  long k_col;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 25 - 1; k++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        ko = k_col * 25 * 25 + j_col * 25 + i_col;
        kd = k_col * 125;
        jd = j_col * 25;
        sum0 = ((orig[ko + 2 + 0] * 4) + (orig[ko + 1 + 0] * 2) + (orig[ko + 0 + 0] * 1) + (orig[ko + 0 + 1] * 1) + (orig[ko + 0 + 2] * 2) + (orig[ko + 1 + 2] * 4)) - (orig[ko + 2 + 2] * 4);
        sum1 = ((orig[ko + 2 + 0 + kd] * 4) + (orig[ko + 1 + 0 + kd] * 2) + (orig[ko + 0 + 0 + kd] * 1) + (orig[ko + 0 + 1 + kd] * 1) + (orig[ko + 0 + 2 + kd] * 2) + (orig[ko + 1 + 2 + kd] * 4)) - (orig[ko + 2 + 2 + kd] * 4);
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[jd + i + 0][jd + j + 0][kd + k + 0] = mul0;
        sol[jd + i + 0][jd + j + 0][kd + k + 124] = mul1;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:45:35: error: invalid operands to binary * (have ‘long int (*)[25]’ and ‘int’)
   45 |         sum0 = ((orig[ko + 2 + 0] * 4) + (orig[ko + 1 + 0] * 2) + (orig[ko + 0 + 0] * 1) + (orig[ko + 0 + 1] * 1) + (orig[ko + 0 + 2] * 2) + (orig[ko + 1 + 2] * 4)) - (orig[ko + 2 + 2] * 4);
      |                      ~            ^
      |                      |
      |