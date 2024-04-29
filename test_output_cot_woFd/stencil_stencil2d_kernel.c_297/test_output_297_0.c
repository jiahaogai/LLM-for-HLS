#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k1;
  int k2;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 2; c < 64 - 2; c++) {
      temp = 0;
      k1 = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k1 < 9) {
        k2 = 0;
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{8}
        while (k2 < 9) {
          i = r - 4 + k1;
          j = c - 4 + k2;
          temp += orig[i * 64 + j] * filter[k1 * 9 + k2];
          k2++;
        }
        k1++;
      }
      sol[r * 64 + c] = temp;
    }
  }
}