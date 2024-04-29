#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 1; j < 8191; j++) {
      idx = ((i - 1) * 8191) + j;
      sol[idx] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      inner:
      for (k = 0; k < 9; k++) {
        int cur = ((center + k) - 45);
        int cur_idx = ((cur - 1) * 8191) + cur;
        sol[idx] += filter[k] * orig[cur_idx];
      }
    }
  }
}