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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8192 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 1; j < 8192 - 1; j++) {
      x = 0;
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
      inner:
      for (y = -1; y <= 1; y++) {
        x += filter[y + 1] * orig[i + y * 8192];
      }
      sol[i * 8192 + j] = x;
    }
  }
}