#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 / 9) * k) + j;
        k_row = i + (-8 + ((8192 / 9) * k));
        tmp += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = tmp;
    }
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}