#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 9) {
        int offset = k - 4;
        int filter_idx = idx + (offset * 8192);
        sol[idx] += filter[k] * center - filter[k] * orig[filter_idx];
        k++;
      }
    }
  }
}