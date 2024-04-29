#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) > -1 ? (k - 4) : 0);
        col = j + ((k - 4) > -1 ? 0 : - (k - 4));
        sum += filter[k] * orig[row * 8 + col];
      }
      sol[i * 8 + j] = sum;
    }
  }
}