#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int pad;
  int r_pad;
  int q_pad;
  int p_pad;
  int r_pad_minus_1;
  int q_pad_minus_1;
  int p_pad_minus_1;
  int r_min;
  int r_max;
  int q_min;
  int q_max;
  int p_min;
  int p_max;
  double sum;
  pad = 1;
  r_pad = 8;
  q_pad = 8;
  p_pad = 8;
  r_pad_minus_1 = r_pad - 1;
  q_pad_minus_1 = q_pad - 1;
  p_pad_minus_1 = p_pad - 1;
  r_min = 0 + r_pad;
  r_max = 8192 + 0 + r_pad_minus_1;
  q_min = 0 + q_pad;
  q_max = 8192 + 0 + q_pad_minus_1;
  p_min = 0 + p_pad;
  p_max = 8192 + 0 + p_pad_minus_1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  loop_r:
  for (r = 0 + r_pad; r < 8192 + 0 + r_pad_minus_1; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_q:
    for (q = 0 + q_pad; q < 8192 + 0 + q_pad_minus_1; q++) {
      sum = 0.0;
      loop_p:
      for (p = 0 + p_pad; p < 8192 + 0 + p_pad_minus_1; p++) {
        sum += filter[pad] * orig[r * 8192 + q * 8192 + p];
      }
      sol[r * 8192 + q] = sum;
    }
  }
}