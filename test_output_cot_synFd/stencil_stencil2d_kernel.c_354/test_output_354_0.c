#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -4 + pad; k < 5 - pad; k++) {
        t += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = t;
    }
  }
}