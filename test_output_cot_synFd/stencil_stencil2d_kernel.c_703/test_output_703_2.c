#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      inner:
      for (k = -1; k < 2; k++) {
        for (int x = -1; x < 2; x++) {
          int orig_idx = (((((i * 8) + j) * 8) + k) * 8) + x + pad;
          sum += orig[orig_idx] * filter[x + 1];
        }
      }
      sol[(i * 8) + j] = sum;
    }
  }
}