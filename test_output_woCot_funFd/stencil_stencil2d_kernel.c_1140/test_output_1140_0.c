#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 128; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (i + ((4 - 2 + ((k + 4) >> 2)) & 63)) * 128 + j + ((8 - 2 + ((k + 4) & 15)) & 127);
        val += orig[idx] * filter[k];
      }
      sol[i * 128 + j] = val;
    }
  }
}