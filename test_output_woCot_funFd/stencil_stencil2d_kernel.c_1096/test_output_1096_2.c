#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int pad;
  int pad2;
  int r_pad;
  int q_pad;
  int p_pad;
  int r_pad2;
  int q_pad2;
  int p_pad2;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  pad = 1;
  pad2 = ((pad << 1) + 1);
  r_pad = (8 + pad);
  q_pad = (8 + pad);
  p_pad = (8 + pad);
  r_pad2 = (r_pad - pad2);
  q_pad2 = (q_pad - pad2);
  p_pad2 = (p_pad - pad2);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (r = 0; r < 8; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (q = 0; q < 8; q++) {
      for (p = 0; p < 8; p++) {
        sum = 0.0;
        for (int k = 0; k < 9; k++) {
          sum += filter[k] * orig[(((p - 1) + pad) + ((q - 1) + pad) * 8) + ((r - 1) + pad) * 81];
        }
        sol[((p - 1) + pad) + ((q - 1) + pad) * 8 + ((r - 1) + pad) * 64] = sum;
      }
    }
  }
}