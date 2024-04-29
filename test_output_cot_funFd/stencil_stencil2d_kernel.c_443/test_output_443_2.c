#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      x = orig[idx] + filter[0] * (orig[idx - 1 + 0 * 256] + orig[idx + 1 + 0 * 256]);
      y = orig[idx] + filter[1] * (orig[idx - 1 + 1 * 256] + orig[idx + 1 + 1 * 256]);
      sol[idx] = x + filter[2] * y;
    }
  }
}