#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 1; r < 128 + 1 - 3; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 1; c < 64 + 1 - 3; c++) {
      mul = 0;
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL reduction=mul FACTOR=auto{1}
        for (i = 0; i < 3; i++) {
          j = k + 3 * i;
          mul += filter[j] * orig[r + k - 1 + 128 * (c + i - 1)];
        }
      }
      sol[r + 128 * c] = mul;
    }
  }
}