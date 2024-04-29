#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 64; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_index = (i + ((4 - 2) + (-7 + k))) * 64 + j + ((4 - 2) + (-7 + k));
        if (cur_index < 0) {
          cur_index = 0;
        }
        if (cur_index >= 8192) {
          cur_index = 8191;
        }
        result += cur_filter * orig[cur_index];
      }
      sol[i * 64 + j] = result;
    }
  }
}