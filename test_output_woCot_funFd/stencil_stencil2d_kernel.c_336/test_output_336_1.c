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
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8188; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (x = -1; x <= 1; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{32}
        for (y = -1; y <= 1; y++) {
          t += filter[((y + 1) * 3) + (x + 1)] * orig[i + y * 8192 + 1 + x * 1];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}