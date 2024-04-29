- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Allow 4 threads to execute this loop concurrently to exploit the processor's instruction level parallelism.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8191; j++) {
      s = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (8192 + i + (-4) * k) % 8192;
        s += ((float )filter[k]) * orig[idx];
      }
      sol[i * 8192 + j] = s;
    }
  }
}