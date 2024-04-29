#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8184; j += 8) {
      temp = 0;
      mul = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (k_col = -4; k_col < 5; k_col++) {
        k = k_col + j;
        if (((k >= 8) && (k < 8184))) {
          mul = filter[k_col + 4] * orig[k];
          temp += mul;
        }
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[j] = temp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8184; j += 8) {
      temp = 0;
      mul = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (k_row = -4; k_row < 5; k_row++) {
        k = k_row + i;
        if (((k >= 8) && (k < 8184))) {
          mul = filter[k_row + 4] * sol[k];
          temp += mul;
        }
      }
      sol[i] = temp;
    }
  }
}