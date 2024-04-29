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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 8178; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      left = orig[idx - 1];
      right = orig[idx + 1];
      top = orig[idx - 8192];
      bottom = orig[idx + 8192];
      sol[idx] = ((left + right + top + bottom + center) / 4) + filter[4] * center;
    }
  }
}