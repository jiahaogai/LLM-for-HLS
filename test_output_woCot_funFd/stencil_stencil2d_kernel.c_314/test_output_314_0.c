#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    row = i * 9;
    middle:
    for (j = 0; j < 9; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        sum += orig[row + k] * filter[k];
      }
      sol[i * 9 + j] = sum;
    }
  }
}