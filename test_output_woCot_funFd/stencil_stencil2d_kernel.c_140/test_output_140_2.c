#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 128; j++) {
      idx = i * 128 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_inner:
      for (k = 0; k < 9; k++) {
        int cur = filter[k];
        int x = i + ((k / 3) - 1);
        int y = j + ((k % 3) - 1);
        if (x < 0) {
          x = 0;
        }
        if (x > 63) {
          x = 63;
        }
        if (y < 0) {
          y = 0;
        }
        if (y > 127) {
          y = 127;
        }
        sol[idx] += cur * orig[x * 128 + y];
      }
    }
  }
}