#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (x = -1 + 8 * (0); x < 8 + 8 * (0); x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (y = -1 + 8 * (0); y < 8 + 8 * (0); y++) {
          t += filter[8 * (x) + y] * orig[i + 8 * (x) + y];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}