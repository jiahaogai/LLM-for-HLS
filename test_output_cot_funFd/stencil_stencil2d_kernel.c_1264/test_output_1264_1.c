#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{8}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        int k = pad + j + (-1 + 0 * (32 + 2 * 1));
        int v = pad + i + (-1 + k_col * (32 + 2 * 1));
        sum += filter[k_col] * orig[v];
      }
      sol[i * (32 + 2 * 1) + j] = sum;
    }
  }
}