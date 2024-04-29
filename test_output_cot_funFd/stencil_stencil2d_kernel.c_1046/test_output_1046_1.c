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
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loop_x:
  for (i = 1; i < 8192 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_y:
    for (j = 1; j < 8192 - 1; j++) {
      x = 0;
      loop_filter:
      for (y = -4; y < 5; y++) {
        x += filter[y + 4] * orig[i + y * 8192];
      }
      sol[i * 8192 + j] = x;
    }
  }
}