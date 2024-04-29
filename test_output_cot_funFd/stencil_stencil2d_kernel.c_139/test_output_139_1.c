#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (c = 0; c < 64; c++) {
      temp = 0;
      mul = 1;
      k1 = r * 64 + c;
      k2 = k1 + 1;
//#pragma ACCEL PARALLEL reduction=temp
      
#pragma ACCEL PARALLEL reduction=temp factor=auto{16}
      for (k2 = k1 + 1; k2 < k1 + 9; k2++) {
        temp += mul * orig[k2];
        mul *= filter[2];
      }
      sol[k1] = temp;
    }
  }
}