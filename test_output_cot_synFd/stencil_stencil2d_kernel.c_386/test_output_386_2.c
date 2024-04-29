#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 2; i < 128 - 2; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 2; j < 64 - 2; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i + ((k - 4) << 6) + ((j - 4) << 1)];
      }
      sol[i + ((pt - 4) << 6) + ((j - 4) << 1)] = t;
    }
  }
}