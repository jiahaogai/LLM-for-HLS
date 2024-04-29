#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int xmin = 1;
  int xmax = 8190;
  int ymin = 1;
  int ymax = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      x = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (y = -4; y <= 4; y++) {
        int tmp = 0;
        tmp = ((y == 0) && (x == 0)) ? 16 : 1;
        x += tmp * orig[i + y * 8192];
      }
      sol[i * 8192 + j] = x;
    }
  }
}