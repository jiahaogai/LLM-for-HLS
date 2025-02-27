#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      inner:
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + ((k - 4) * 64)];
      }
    }
  }
}