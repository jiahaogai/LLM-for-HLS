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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        for (int x = -1 * pad; x <= 1 * pad; x++) {
          int i_pad = i + pad;
          int j_pad = j + pad;
          t += filter[((k + 1) * 3) + (x + 1)] * orig[i_pad * 8 + j_pad * 1 + k * 8 + x];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}