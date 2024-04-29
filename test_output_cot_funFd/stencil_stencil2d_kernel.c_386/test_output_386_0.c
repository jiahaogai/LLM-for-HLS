#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 1; r < 128 + 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c < 64 + 1; c++) {
      i = r - 1;
      j = c - 1;
      k = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      while (k < 9) {
        sol[r * 64 + c] += filter[k] * orig[i * 64 + j];
        j++;
        k++;
      }
    }
  }
}