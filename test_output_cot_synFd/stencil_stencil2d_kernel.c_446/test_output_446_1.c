#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 32 + 1 - 1; j++) {
      idx = i * 32 + j;
      val = ((0 * (orig[idx - 32 - 1] - sol[idx - 32 - 1])) + (1 * (orig[idx - 32] - sol[idx - 32])) + (2 * (orig[idx - 32 + 1] - sol[idx - 32 + 1])) + (3 * (orig[idx - 1] - sol[idx - 1])) + (4 * (orig[idx + 1] - sol[idx + 1])) + (5 * (orig[idx + 32 - 1] - sol[idx + 32 - 1])) + (6 * (orig[idx + 32] - sol[idx + 32])) + (7 * (orig[idx + 32 + 1] - sol[idx + 32 + 1])));
      sol[idx] = val / 42;
    }
  }
}