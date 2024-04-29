#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int curFilter;
        int curIndex;
        curFilter = filter[k];
        curIndex = (256 + i - 4) * 256 + j - 4 + k;
        if (curIndex < 0) {
          curIndex = 0;
        }
        if (curIndex > 8191) {
          curIndex = 8191;
        }
        result += curFilter * orig[curIndex];
      }
      sol[i * 256 + j] = result;
    }
  }
}