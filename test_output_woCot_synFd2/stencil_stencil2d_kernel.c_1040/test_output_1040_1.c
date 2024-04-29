#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      flatten_row = i * 64 + j;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k * 8 + j;
        row = flatten_row - 1 + ((k - 4) * 64);
        col = flatten_col - 1 + ((j - 4) * 8);
        if (row < 0 || row > 8191) {
          continue;
        }
        if (col < 0 || col > 8191) {
          continue;
        }
        sol[row] += orig[col] * filter[k];
      }
    }
  }
}