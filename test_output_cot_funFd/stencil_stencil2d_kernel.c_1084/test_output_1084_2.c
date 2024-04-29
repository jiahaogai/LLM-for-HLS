Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
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
        int orig_idx = (i + (-1 + k)) * 256 + j + (-1 + k);
        if (orig_idx < 0) {
          orig_idx = 0;
        }
        if (orig_idx > 8191) {
          orig_idx = 8191;
        }
        result += orig[orig_idx] * filter[k];
      }
      sol[i * 256 + j] = result;
    }
  }
}