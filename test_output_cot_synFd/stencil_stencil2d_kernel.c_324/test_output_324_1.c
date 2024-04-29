#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
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
    inner:
    for (j = 0; j < 128 + 2; j++) {
      x = i - 1;
      y = j - 1;
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      middle:
      for (int _in_ = 0; _in_ < 9; _in_++) {
        int _in = _in_ + 4;
        if ((((x + _in) >= 0) && ((x + _in) < 128))) {
          if ((((y + _in) >= 0) && ((y + _in) < 128))) {
            t += ((orig[((x + _in) * 128) + y + _in]) * (filter[_in_]));
          }
        }
      }
      sol[((i - 1) * 128) + (j - 1)] = t;
    }
  }
}