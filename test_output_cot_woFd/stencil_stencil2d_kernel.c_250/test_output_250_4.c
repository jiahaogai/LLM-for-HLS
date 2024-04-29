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
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj)];
        }
      }
      sol[i * 64 + (j * 8 + 0)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 1)];
        }
      }
      sol[i * 64 + (j * 8 + 1)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 2)];
        }
      }
      sol[i * 64 + (j * 8 + 2)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 3)];
        }
      }
      sol[i * 64 + (j * 8 + 3)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 4)];
        }
      }
      sol[i * 64 + (j * 8 + 4)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 5)];
        }
      }
      sol[i * 64 + (j * 8 + 5)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 6)];
        }
      }
      sol[i * 64 + (j * 8 + 6)] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + pad) * 3) + (jj + pad)] * orig[i * 64 + (j * 8 + jj + 7)];
        }
      }
      sol[i * 64 + (j * 8 + 7)] = t;
    }
  }
}