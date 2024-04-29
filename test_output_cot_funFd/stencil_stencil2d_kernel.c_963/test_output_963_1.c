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
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 8191; j++) {
      r = 4 * (i - 1) + 1;
      c = 4 * (j - 1) + 1;
      temp = ((orig[r - 1, c - 1] + orig[r - 1, c] + orig[r - 1, c + 1] + orig[r, c - 1] + orig[r, c] + orig[r, c + 1] + orig[r + 1, c - 1] + orig[r + 1, c] + orig[r + 1, c + 1]) / 9);
      sol[r, c] = temp;
    }
  }
}