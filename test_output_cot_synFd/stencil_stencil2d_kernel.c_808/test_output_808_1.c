#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int fltr;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      idx = i * (64 + 8) + j;
      fltr = 0;
      
#pragma ACCEL PARALLEL reduction=fltr FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        fltr += filter[k] * orig[idx + align(k - 4, (64 + 8))];
      }
      sol[idx] = fltr;
    }
  }
}