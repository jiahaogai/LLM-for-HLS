#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      s = 0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (i + k) * 8192 + j;
        s += filter[4 + k] * orig[idx];
      }
      sol[i * 8192 + j] = s;
    }
  }
}