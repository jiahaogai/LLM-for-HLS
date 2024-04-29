#pragma ACCEL kernel stencil

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int fl;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 1; r < 8190; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8190; c++) {
      sol[r * 8192 + c] = 0.0;
      fl = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (i = -4; i <= 4; i++) {
        fl = fl + filter[i + 4] * orig[(r + i) * 8192 + c];
      }
      sol[r * 8192 + c] = fl;
    }
  }
}