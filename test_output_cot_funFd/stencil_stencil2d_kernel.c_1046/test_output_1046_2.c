#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int xmax = 8192 - 1;
  int ymax = 8192 - 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loopj:
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 8192 - 1; i++) {
      x = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        y = i - 4 + k;
        if (y < 0 || y > 8191) {
          x = x + 0;
        }
         else {
          x = x + orig[y];
        }
      }
      sol[j * 8192 + i] = x;
    }
  }
}