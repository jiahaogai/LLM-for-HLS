#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
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
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      compute:
      for (x = -4; x < 5; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        inner_compute:
        for (y = -4; y < 5; y++) {
          t += orig[((i + x) + 8192) * 8 + ((j + y) + 0)] * filter[x + 4];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}