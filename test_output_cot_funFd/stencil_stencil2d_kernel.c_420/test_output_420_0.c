#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int temp_orig;
  int temp_sol;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      temp_orig = orig[i - 1 + (j - 1) * 8191];
      sum_filter:
      for (k_col = 0; k_col < 9; k_col++) {
        k = k_col - 4;
        row = i + k;
        col = j + k;
        if (row < 1) {
          row = 1;
        }
        if (row > 8191) {
          row = 8191;
        }
        if (col < 1) {
          col = 1;
        }
        if (col > 8191) {
          col = 8191;
        }
        temp_sol += filter[k_col] * orig[row - 1 + col - 1 * 8191];
      }
      sol[i - 1 + j - 1 * 8191] = temp_sol;
      temp_sol = 0;
    }
  }
}