#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 8; j < 8192; j += 8) {
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
      for (k_col = -4; k_col <= 4; k_col++) {
        k = k_col + j;
        if ((k >= 8) && (k < 8192)) {
          temp += filter[4 + k_col] * orig[k];
        }
      }
      sol[j] = temp;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8192; j += 8) {
      orig[i + 1] = sol[j];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8192; j += 8) {
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{8}
      for (k_row = -4; k_row <= 4; k_row++) {
        k = i + k_row;
        if ((k >= 8) && (k < 8184)) {
          temp += filter[4 + k_row] * orig[k];
        }
      }
      sol[j] = temp;
    }
  }
}