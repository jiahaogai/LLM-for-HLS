#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  int jj;
  int kk;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        jj = j - 4 + ((k + 4) >> 5);
        kk = k - 4 & 0x07;
        result += filter[k] * orig[i * 256 + jj * 64 + kk * 8];
      }
      sol[i * 256 + j] = result;
    }
  }
}