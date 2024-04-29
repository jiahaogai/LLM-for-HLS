#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      idx = i * (64 + 8) + j;
      x = 0;
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        y = k + j;
        if (y < 0 || 64 + 8 <= y) {
          continue;
        }
        x += filter[k + 4] * orig[idx + y * (64 + 8)];
      }
      sol[idx] = x;
    }
  }
}