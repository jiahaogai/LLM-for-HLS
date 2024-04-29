#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    inner:
    for (j = 0; j < 256; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{4}
      middle:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k % 3) - 1);
        int orig_idx = k_col + (j + ((k / 3) - 1)) * 256;
        buf[k] = orig[orig_idx];
        sum += buf[k] * filter[k];
      }
      sol[i + j * 256] = sum;
    }
  }
}