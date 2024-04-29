#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 256; j++) {
      result = 0;
      middle:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_index = (i + ((4 - (k / 3))) * 8) * 256 + j + ((k % 3) * 8);
        result += cur_filter * orig[cur_index];
      }
      sol[i * 256 + j] = result;
    }
  }
}