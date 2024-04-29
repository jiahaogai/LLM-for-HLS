#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      x = 0;
      y = -1;
      filter:
      for (k = 0; k < 9; k++) {
        if ((((i + y) >= 0) && ((i + y) < 256)) && (((j + x) >= 0) && ((j + x) < 256))) {
          x++;
          if (x == 9) {
            x = 0;
            y++;
          }
          sol[idx] += orig[((i + y) * 256) + ((j + x) * 1)] * filter[k];
        }
      }
    }
  }
}