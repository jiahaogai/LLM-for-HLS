#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner_1:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 1 + ((0 + k - 4) % 256)) % 256;
        val += filter[k] * orig[idx * 256 + j];
      }
      sol[i * 256 + j] = val;
    }
  }
}