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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (r < 32) {
    c = 0;    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (c < 32) {
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{9}
      for (k = 0; k < 9; k++) {
        k1 = r + ((k / 3) - 1);
        k2 = c + ((k % 3) - 1);
        mul = orig[((k1 * 32) + k2)] * filter[k];
        temp += mul;
      }
      sol[((r * 32) + c)] = temp;
      c++;
    }
    r++;
  }
}