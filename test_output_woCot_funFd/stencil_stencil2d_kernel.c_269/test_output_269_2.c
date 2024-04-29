#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner_reduction:
      for (k = -4; k < 5; k++) {
        sum += filter[((k + 4) >> 2)] * orig[i + k * 8];
      }
      sol[i * 8 + j] = sum;
    }
  }
}