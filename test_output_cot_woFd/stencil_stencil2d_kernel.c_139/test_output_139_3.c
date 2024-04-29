#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 0; c < 64 + 2; c++) {
      temp = 0;
      mul = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        mul = filter[k] * orig[r * (64 + 2) + c + (-1 + k)];
        temp += mul;
      }
      sol[r * (64 + 2) + c] = temp;
    }
  }
}