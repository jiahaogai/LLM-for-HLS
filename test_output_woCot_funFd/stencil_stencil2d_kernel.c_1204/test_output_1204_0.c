#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 2; i < 128 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 2; j < 64 - 1; j++) {
      i_col = i - 1;
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
      inner:
      for (k = 0; k < 3; k++) {
        k_col = k - 1;
        temp += filter[k] * orig[i_col * 64 + j_col];
      }
      sol[i * 64 + j] = temp;
    }
  }
}