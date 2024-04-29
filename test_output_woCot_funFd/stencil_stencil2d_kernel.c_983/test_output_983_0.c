#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int left;
  int right;
  int top;
  int bottom;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      center = orig[idx];
      left = i == 0 ? 0 : orig[idx - 1];
      right = i == 255 ? 0 : orig[idx + 1];
      top = j == 0 ? 0 : orig[idx - 256];
      bottom = j == 255 ? 0 : orig[idx + 256];
      sol[idx] = ((left + right + top + bottom) - center) * filter[4] + center;
    }
  }
}