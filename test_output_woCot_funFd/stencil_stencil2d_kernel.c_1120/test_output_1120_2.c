Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    middle:
    for (j = 1; j < 8191; j++) {
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int idx = i + (-1 + ((k % 3) - 1));
        int flt_idx = k;
        sol[i * 8192 + j] += filter[flt_idx] * orig[idx * 8192 + j + (-1 + ((k / 3) - 1))];
      }
    }
  }
}