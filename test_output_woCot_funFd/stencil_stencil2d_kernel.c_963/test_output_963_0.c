#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      temp = 0;
      r = i - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      while (r <= i + 4) {
        c = j - 4;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        while (c <= j + 4) {
          temp += filter[((r - i) + 4) * 5 + (c - j) + 4] * orig[r * 8192 + c];
          c++;
        }
        r++;
      }
      sol[i * 8192 + j] = temp;
    }
  }
}