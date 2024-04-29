#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idx0;
  int flatten_i;
  int flatten_j;
  int range_l;
  int range_r;
  int range_t;
  int range_b;
  int range;
  int idx_up;
  int idx_down;
  int idx_left;
  int idx_right;
  int idx_up_left;
  int idx_up_right;
  int idx_down_left;
  int idx_down_right;
  int idx_sm;
  int filt_sm;
  range_l = 1;
  range_r = 1;
  range_t = 1;
  range_b = 1;
  idx_up = 8193;
  idx_down = -1;
  idx_left = 8193;
  idx_right = -1;
  idx_up_left = 8194;
  idx_up_right = 8195;
  idx_down_left = -1;
  idx_down_right = -1;
  flatten_i = 1;
  flatten_j = 1;
  range = 2;
  idx = 0;
  while (flatten_i < 8192 + 1 - range) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{126}
    while (flatten_j < 8192 + 1 - range) {
      idx_sm = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (idx_sm < 9) {
        filt_sm = filter[idx_sm];
        idx = flatten_i + idx_up * range + idx_sm;
        sol[idx] = orig[idx] + filt_sm * (orig[idx + idx_up_left] + orig[idx + idx_up_right] + orig[idx + idx_down_left] + orig[idx + idx_down_right] + orig[idx + idx_left] + orig[idx + idx_right] + orig[idx]);
        idx_sm++;
      }
      flatten_j += 1;
    }
    flatten_i += 1;
    flatten_j = 1;
  }
}