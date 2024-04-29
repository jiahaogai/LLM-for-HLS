#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
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
      val = 0.0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        val += filter[k + 4] * orig[idx + k];
      }
      sol[idx] = val;
    }
  }
}