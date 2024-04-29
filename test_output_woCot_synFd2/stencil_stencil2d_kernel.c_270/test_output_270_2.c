#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (i * 256 + j) * 256 + k;
        val += filter[(((k + 4) < 0 ? (-1 * (k + 4)) : (k + 4))) - 4] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}