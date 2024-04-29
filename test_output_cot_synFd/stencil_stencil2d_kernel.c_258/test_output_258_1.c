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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      k = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      while (k < 9) {
        sol[idx] += filter[k] * center;
        k++;
      }
    }
  }
}