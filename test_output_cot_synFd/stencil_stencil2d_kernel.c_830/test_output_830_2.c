#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      loopk:
      for (k = 0; k < 9; k++) {
        idx = (8192 + orig[-8192 + k] + i) % 8192;
        sum += filter[k] * orig[idx];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}