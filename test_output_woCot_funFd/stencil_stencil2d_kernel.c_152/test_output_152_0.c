#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      t = 0;
      x = -1 + 8 * i;
      y = -1 + 8 * j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int _in_ = 0; _in_ < 9; _in_++) {
        t += filter[_in_] * orig[x + _in_ * 8];
      }
      sol[x + y * 8] = t;
    }
  }
}