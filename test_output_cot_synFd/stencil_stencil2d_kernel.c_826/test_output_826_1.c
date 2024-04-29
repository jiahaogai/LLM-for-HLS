#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  int total;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        buf[k] = orig[((i + (-4 + ((k >> 1) & 8)))) * 256 + ((j + (-4 + ((k & 1) * 8))))];
      }
      total = 0;
      inner_1:
      for (k = 0; k < 9; k++) {
        total += buf[k] * filter[k];
      }
      sol[i * 256 + j] = total;
    }
  }
}