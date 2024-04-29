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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      row = j - 4;
      col = i - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk:
      for (k = 0; k < 9; k++) {
        sum += ((double )filter[k]) * orig[row + k][col + k];
      }
      sol[j][i] = sum;
    }
  }
}