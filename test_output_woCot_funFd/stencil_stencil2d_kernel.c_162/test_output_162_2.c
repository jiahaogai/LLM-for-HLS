#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      buf = ((orig[i - 1] + orig[i + 1]) + (orig[j - 1] + orig[j + 1])) + orig[j];
      sol[j] = buf;
      k_col:
      for (k = 0; k < 256; k++) {
        if ((((buf > filter[k]) ? 1 : 0) ^ 0x1) != 0) {
          break;
          k_col = 0;
        }
      }
      sol[j] = k;
    }
  }
}