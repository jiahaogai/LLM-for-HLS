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
  loopj:
  for (j = ymin; j <= ymax; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = xmin; i <= xmax; i++) {
      x = i - 1;
      if (x < xmin) {
        x = xmin;
      }
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{8}
      loopx:
      for ( ; x <= xmax; x++) {
        y = j - 1;
        if (y < ymin) {
          y = ymin;
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{8}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopy:
        for ( ; y <= ymax; y++) {
          sol[j * 8192 + i] += orig[y * 8192 + x] * filter[y - j + 4];
        }
      }
    }
  }
}