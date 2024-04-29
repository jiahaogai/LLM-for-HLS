#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  r = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  while (r < 8) {
    c = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (c < 8) {
      temp = 0;
      k1 = r * 8 - 1;
      k2 = c * 8 - 1;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        mul = orig[k1 + k2 + 1] * filter[k];
        temp += mul;
      }
      sol[r * 8 + c] = temp;
      c++;
    }
    r++;
  }
}