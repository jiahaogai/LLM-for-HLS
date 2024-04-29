#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        if ((i + k) < 0 || (i + k) > 255) {
          t += filter[k + 4] * 0;
        }
         else {
          t += filter[k + 4] * orig[(i + k) * 256 + j];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}