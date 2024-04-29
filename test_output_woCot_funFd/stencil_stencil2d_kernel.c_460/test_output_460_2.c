#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int xmin = 1;
  int xmax = 8191;
  int ymin = 1;
  int ymax = 8191;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      x = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (y = -4; y <= 4; y++) {
        int tmp;
        tmp = orig[i + y * 8192];
        x += filter[4 + y] * tmp;
      }
      sol[i * 8192 + j] = x;
    }
  }
}