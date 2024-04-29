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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 256;
      flatten_row = i * 32 - 1;
      flatten_col = j * 32 - 1;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        int cur_filter;
        int cur_row;
        int cur_col;
        cur_filter = filter[k];
        cur_row = flatten_row + k;
        cur_col = flatten_col + k;
        if (cur_row < 0 || cur_row >= 8192 || cur_col < 0 || cur_col >= 8192) {
          orig[row + col + k] = 0;
        }
        else {
          orig[row + col + k] = cur_filter * orig[cur_row * 256 + cur_col];
        }
      }
    }
  }
}