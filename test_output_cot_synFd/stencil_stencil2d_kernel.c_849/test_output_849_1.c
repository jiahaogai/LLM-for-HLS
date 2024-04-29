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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      inner:
      for (x = -1; x <= 1; x++) {
        for (y = -1; y <= 1; y++) {
          t += filter[4 + x] * orig[i + x + ((j + y) * 8192)] ;
        }
      }
      sol[i + ((j) * 8192)] = t;
    }
  }
}