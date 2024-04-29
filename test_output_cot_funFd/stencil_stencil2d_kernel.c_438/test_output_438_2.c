Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{2}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        row = i - 4 + k / 8190;
        col = j - 4 + k % 8190;
        sum += filter[k] * orig[row * 8190 + col];
      }
      sol[i * 8190 + j] = sum;
    }
  }
}