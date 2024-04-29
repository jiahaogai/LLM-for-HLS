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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      x = orig[idx] * filter[0] + (orig[idx + 1] * filter[1]) + (orig[idx + 2] * filter[2]) + (orig[idx + 256] * filter[3]) + (orig[idx + 512] * filter[4]) + (orig[idx + 768] * filter[5]) + (orig[idx + 1024] * filter[6]) + (orig[idx + 1280] * filter[7]) + (orig[idx + 1536] * filter[8]);
      y = x < 0 ? 0 : x;
      sol[idx] = y;
    }
  }
}