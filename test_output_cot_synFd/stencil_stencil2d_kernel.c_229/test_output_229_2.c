#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_index = (256 + i - ((8 - k) / 2)) % 256;
        int cur_j = (256 + j - ((8 - k) / 2)) % 256;
        result += cur_filter * orig[cur_index * 256 + cur_j];
      }
      sol[i * 256 + j] = result;
    }
  }
}