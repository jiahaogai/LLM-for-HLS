#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[idx + dir[k]];
      }
      sol[idx] = sum;
    }
  }
}