#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int t;
  int x;
  int y;
  x = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  y = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (y < 64) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    while (x < 128) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (j = 0; j < 3; j++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (i = 0; i < 3; i++) {
          idx = x + i - 1;
          idy = y + j - 1;
          if (idx < 0) {
            idx = 0;
          }
          
#if 0
          if (idx > 127) {
            idx = 127;
          }
          
#endif
          if (idy < 0) {
            idy = 0;
          }
          
#if 0
          if (idy > 63) {
            idy = 63;
          }
          
#endif
          t += filter[i + j * 3] * orig[idx + idy * 128];
        }
      }
      sol[x + y * 128] = t;
      x++;
    }
    x = 0;
    y++;
  }
}