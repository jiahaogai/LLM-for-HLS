Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        cur = orig[i * 8 + j + k];
        sum += cur;
      }
      sol[i * 8 + j] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer_2:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle_2:
    for (j = 0; j < 8; j++) {
      int sum = 0;
      int pad;
      pad = 1;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner_2:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        cur = sol[(((i - 1) * 8) + j) + k];
        sum += cur;
      }
      sol[i * 8 + j] = sum;
    }
  }
}