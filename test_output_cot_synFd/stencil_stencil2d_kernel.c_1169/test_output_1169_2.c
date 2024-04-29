#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 1; i < 8191; i++) {
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = 0;
/* Standardize from: for(k = -4; k < 5; k++) {...} */
      inner:
      for (k = -4; k < 5; k++) {
        int cur = k + center;
        int cur_idx = ((cur * 8192) + j);
        /* Boundary check */
        if (cur < 0 || cur > 8191) {
          sol[idx] += 0;
        } else {
          sol[idx] += ((orig[cur_idx]) * (filter[cur + 4]));
        }
      }
    }
  }
}