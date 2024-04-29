#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (x = -1; x < 2; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{32}
        for (y = -1; y < 2; y++) {
          t += filter[x + 1] * filter[y + 1] * orig[(i + x) * 8192 + (j + y)];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}