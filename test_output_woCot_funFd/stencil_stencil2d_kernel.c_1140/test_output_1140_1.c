#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 128; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) >> 6);
        col = j + ((k - 4) & 63);
        sum += filter[k] * orig[row * 128 + col];
      }
      sol[i * 128 + j] = sum;
    }
  }
}