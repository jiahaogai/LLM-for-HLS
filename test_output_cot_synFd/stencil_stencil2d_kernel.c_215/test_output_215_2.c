#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0 - pad; k < 8 - pad; k++) {
        t += filter[k + pad] * orig[i + k * 8192];
      }
      sol[i + j * 8192] = t;
    }
  }
}