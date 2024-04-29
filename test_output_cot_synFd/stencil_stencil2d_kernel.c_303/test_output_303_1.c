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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 8; j++) {
      row = ((i - 1) * 8) + j;
      inner:
      for (k = 0; k < 9; k++) {
        col = ((k - 1) * 8) + j;
        sum += orig[row * 8 + col] * filter[k];
      }
      sol[row * 8 + j] = sum;
      sum = 0;
    }
  }
}