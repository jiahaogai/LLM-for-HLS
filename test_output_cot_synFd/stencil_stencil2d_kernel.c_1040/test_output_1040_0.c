#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * center;
        center = sol[idx];
      }
    }
  }
}