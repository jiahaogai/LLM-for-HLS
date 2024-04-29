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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1; k <= 1; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1; jj <= 1; jj++) {
          t += filter[((k + 1) * 3) + (jj + 1)] * orig[i * 64 + (j * 8 + k) * 16 + jj * 16];
        }
      }
      sol[i * 64 + j * 8] = t;
    }
  }
}