#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 256; j++) {
      row = i - 4;
      col = j - 4;
      flatten_row = row & 7;
      flatten_col = col & 7;
      idx = (row >> 3) * 8 + (col >> 3);
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      filter:
      for (k = 0; k < 9; k++) {
        int cur_row;
        int cur_col;
        cur_row = flatten_row + ((k >> 3) & 7);
        cur_col = flatten_col + (k & 7);
        int idx_src = (cur_row << 3) + cur_col;
        val += orig[idx_src] * filter[k];
      }
      sol[idx] = val;
    }
  }
}