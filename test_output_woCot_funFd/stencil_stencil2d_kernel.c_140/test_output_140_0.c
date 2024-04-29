#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int offset = k - center;
        int x = i + offset / 128;
        int y = j + offset % 128;
        if (x < 1 || x > 64 - 1 || y < 1 || y > 128 - 1) {
          orig[idx] = 0;
        }
        sol[idx] += filter[k] * orig[x * 128 + y];
      }
    }
  }
}