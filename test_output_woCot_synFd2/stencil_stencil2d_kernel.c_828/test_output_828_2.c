#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur = filter[k] * orig[i + (k - 4) & 255];
        result += cur;
      }
      sol[i * 256 + j] = result;
    }
  }
}