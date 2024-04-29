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
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (x = -1 + 8; x < 8 + 1; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (y = -1 + 8; y < 8 + 1; y++) {
          t += filter[x + 8] * filter[y + 8] * orig[(i - 1 + x) * 8 + (j - 1 + y)];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}