#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 1; c < 33; c++) {
      temp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        i = r + (-1 + k);
        j = c + (-1 + k);
        temp += filter[k] * orig[i * 32 + j];
      }
      sol[r * 32 + c] = temp;
    }
  }
}