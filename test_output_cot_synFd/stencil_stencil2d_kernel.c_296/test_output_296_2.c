#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8178; j++) {
      idx = (i * 8192) + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        int temp = filter[k] * orig[idx + ((k - center) * 8192)];
        sol[idx] += temp;
      }
    }
  }
}