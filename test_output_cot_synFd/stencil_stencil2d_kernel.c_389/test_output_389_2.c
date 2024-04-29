Code: ### Sample Output:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = (i - 4 + 8192) % 8192;
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = (k - 4 + 8192) % 8192;
        sum += orig[i_col * 8192 + k_col] * filter[k];
      }
      sol[j] = sum;
    }
  }
}