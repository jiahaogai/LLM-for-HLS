#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  int xmin = 1;
  int xmax = 8190;
  int ymin = 1;
  int ymax = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loopj:
  for (j = 1; j < 8190; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8190; i++) {
      idx = i + j * 8190;
      sol[idx] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        x = i - 1 + k % 3;
        y = j - 1 + k / 3;
        if (xmin <= x && x <= xmax && ymin <= y && y <= ymax) {
          sol[idx] += filter[k] * orig[x + y * 8190];
        }
      }
    }
  }
}