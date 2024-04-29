#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      val = 0.0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + d[k]];
      }
      sol[idx] = val;
    }
  }
}