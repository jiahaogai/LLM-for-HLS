#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 64 + 2 * 1; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter;
        int cur_arr;
        cur_filter = filter[k];
        cur_arr = orig[(((i + pad) - 1) + ((j + pad) - 1) * 128) - pad * 128];
        t += cur_filter * cur_arr;
      }
      sol[i * 64 + j] = t;
    }
  }
}