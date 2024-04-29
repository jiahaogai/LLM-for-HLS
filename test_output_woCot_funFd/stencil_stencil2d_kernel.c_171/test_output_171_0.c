#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int bound;
  bound = 8192 - 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < bound - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 1; j < bound - 1; j++) {
      t = filter[0] * orig[i * bound + j - 1] + filter[1] * orig[i * bound + j] + filter[2] * orig[i * bound + j + 1] + filter[3] * orig[i * bound + j - bound] + filter[4] * orig[i * bound + j + bound] + filter[5] * orig[i * bound + j - 2 * bound] + filter[6] * orig[i * bound + j + 2 * bound] + filter[7] * orig[i * bound + j - 3 * bound] + filter[8] * orig[i * bound + j + 3 * bound];
      sol[i * bound + j] = t;
    }
  }
}