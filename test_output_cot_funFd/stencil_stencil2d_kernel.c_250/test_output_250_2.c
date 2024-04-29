#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 9) {
        int filter_elem = filter[k];
        int offset = filter_elem * 8192;
        int row_up = idx - offset;
        int row_down = idx + offset;
        int up_avail = row_up >= 0 ? 1 : 0;
        int down_avail = row_down < 8192 ? 1 : 0;
        if ((up_avail & down_avail) != 0) {
          int min_row = (up_avail != 0) ? row_up : row_down;
          int max_row = (up_avail != 0) ? row_down : row_up;
          int row = min_row + (rand() % (max_row - min_row + 1));
          sol[idx] = orig[row];
        }
        k++;
      }
    }
  }
}