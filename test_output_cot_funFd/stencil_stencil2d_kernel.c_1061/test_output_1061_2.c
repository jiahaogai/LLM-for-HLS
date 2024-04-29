#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int bound;
  int xbound;
  int ybound;
  int range;
  int len;
  int fr;
  int fl;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  bound = 32;
  xbound = bound + 1;
  ybound = bound + 1;
  range = bound * 2 + 1;
  len = 8192 / range;
  fr = 4;
  fl = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < len; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8192; j++) {
      x = j % bound;
      y = j / bound;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (y = y - fl; y <= y + fr; y++) {
        for (x = x - fl; x <= x + fr; x++) {
          if (y == -1 || y == ybound || x == -1 || x == xbound) {
            tmp += filter[0] * orig[y * xbound + x];
          }
          else {
            tmp += filter[((y - 1) * 3 + x - 1) + 1] * orig[y * xbound + x];
          }
        }
      }
      sol[j] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8192; j++) {
      orig[j] = sol[j];
    }
  }
}