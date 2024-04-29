#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int idx;
  int center;
  int r;
  int r_up;
  int r_down;
  int c;
  int c_up;
  int c_down;
  int r_max;
  int r_min;
  int c_max;
  int c_min;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_r:
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_c:
    for (c = 1; c < 33; c++) {
      idx = r * 32 + c;
      center = orig[idx];
      r_up = r - 1;
      r_down = r + 1;
      c_up = c - 1;
      c_down = c + 1;
      r_max = (r_up < 0) ? 0 : ((r_up > 32) ? 32 : r_up);
      r_min = (r_down < 0) ? 0 : ((r_down > 32) ? 32 : r_down);
      c_max = (c_up < 0) ? 0 : ((c_up > 32) ? 32 : c_up);
      c_min = (c_down < 0) ? 0 : ((c_down > 32) ? 32 : c_down);
      sol[idx] = ((filter[4] * center) + (filter[3] * (((orig[r * 32 + c_min]) + (orig[r * 32 + c_max])) / 2)) + (filter[2] * (((orig[r_min * 32 + c]) + (orig[r_max * 32 + c])) / 2)) + (filter[1] * (((orig[r_min * 32 + c_min]) + (orig[r_min * 32 + c_max]) + (orig[r_max * 32 + c_min]) + (orig[r_max * 32 + c_max])) / 4)) + (filter[0] * ((orig[r_up * 32 + c_up]) + (orig[r_up * 32 + c_down]) + (orig[r_down * 32 + c_up]) + (orig[r_down * 32 + c_down])) / 4)) / 256;
    }
  }
}