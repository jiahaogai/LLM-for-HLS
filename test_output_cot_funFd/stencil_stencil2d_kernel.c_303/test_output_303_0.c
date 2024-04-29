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
  loop:
/* Standardize from: for(i = 1; i < 8191; i++) {...} */
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner1:
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      int_loop:
      for (k = 0; k < 9; k++) {
        row = i + (-1 + k);
        col = j + (-1 + k);
        sum += filter[k] * orig[row * 8192 + col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}