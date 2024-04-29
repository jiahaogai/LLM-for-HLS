#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      x = i - 1;
      y = j - 1;
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        if ((((x + k) >= 0) && ((x + k) < 128))) {
          
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
          inner_1:
          for (t = 0; t < 9; t++) {
            if ((((y + t) >= 0) && ((y + t) < 128))) {
              t = (filter[k] * orig[((x + k) * 128) + (y + t)]) + t;
            }
          }
        }
      }
      sol[((i - 1) * 128) + (j - 1)] = t;
    }
  }
}