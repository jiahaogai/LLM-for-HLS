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
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 - 1; j++) {
      s = 0.0;
      for (k = 0; k < 9; k++) {
        idx = (i + ((0 - 4 + k)/5)) * 64 + j + ((0 - 4 + k) % 5);
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 64 + j] = s;
    }
  }
}