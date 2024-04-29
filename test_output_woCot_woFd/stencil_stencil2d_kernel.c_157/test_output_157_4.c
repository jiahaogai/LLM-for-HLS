#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int xmin = 1;
  int xmax = 128 + 1;
  int ymin = 1;
  int ymax = 64 + 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 128 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1; j++) {
      x = 0;
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
      for (y = -1; y <= 1; y++) {
        
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{16}
        for (int _in_ = -1; _in_ <= 1; _in_++) {
          x += filter[y + 1] * orig[i + _in_ * 128 - 1];
        }
      }
      sol[i - 1 + (j - 1) * 128] = x;
    }
  }
}