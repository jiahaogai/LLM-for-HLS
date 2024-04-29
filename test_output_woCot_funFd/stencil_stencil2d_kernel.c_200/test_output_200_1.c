#pragma ACCEL kernel stencil

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int offset = k - center;
        int filter_idx = offset + 4;
        int orig_idx = i + offset * 8192 + j;
        sol[idx] += filter[filter_idx] * orig[orig_idx];
      }
    }
  }
}