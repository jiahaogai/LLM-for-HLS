#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    for (c = 2; c < 64 - 2; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k2 = 0; k2 < 9; k2++) {
        k1 = k2 + 1;
        temp += mul * orig[r * 64 + (c - 1 + 64) * 8 + k1];
        mul *= filter[k1];
      }
      sol[r * 64 + (c - 1 + 64) * 8] = temp;
    }
  }
}