Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4 + pad; k < 4 + pad; k++) {
        if ((k < -pad) || (k > 7)) {
          t += orig[i + k] * filter[0];
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        else {
          t += orig[i + k] * filter[4 + k];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}