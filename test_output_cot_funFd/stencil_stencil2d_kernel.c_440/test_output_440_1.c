#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 64 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loopk_col:
    for (k_col = 1; k_col < 9 - 1; k_col++) {
      k_row = 4 + 1 - k_col;
      loopk_row:
      for (k_row = 4 + 1 - k_col; k_row < 64 - 1; k_row++) {
        idx = (k_row * 64) + k_col;
        s = filter[k_col + 4] * orig[idx];
        for (k = 1; k < 5; k++) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          loopk:
          for (k = 1; k < 5; k++) {
            s += filter[k + 4 - k_col] * orig[idx + k * 64];
          }
        }
        sol[idx] = s;
      }
    }
  }
}