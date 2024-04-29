#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 256; i < 8192 - 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 256; j < 8192 - 256; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      inner:
      for (k = -4; k < 5; k++) {
        t += filter[pt + k] * orig[i + k * 8];
      }
      sol[i * 8 + j] = t;
    }
  }
}