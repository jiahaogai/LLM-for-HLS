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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + (-1 + k);
        col = j + (-1 + k);
        if (row < 1 || row > 8191) {
          row = 1;
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (col < 1 || col > 8191) {
          col = 1;
        }
        sum += orig[row * 8192 + col] * filter[k];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}