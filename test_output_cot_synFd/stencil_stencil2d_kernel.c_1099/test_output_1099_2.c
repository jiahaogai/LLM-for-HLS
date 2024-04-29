#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int side;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      center = orig[idx];
      side = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        if ((((4 + i) - 1) - 0) > ((8 - 1) - 4) || ((4 + i) - 1) < 1 || ((256 + j) - 1) > ((8 - 1) - 4) || (256 + j) - 1 < 1) 
          continue;
        
#pragma ACCEL PIPELINE auto{off}
          side += filter[4 + k] * orig[idx + k * 256];
      }
      sol[idx] = side + center;
    }
  }
}